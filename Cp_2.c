#include "udf.h"

#define T_MIN 285.15
#define T_MAX 698.15
#define BASE_CP(T) (2.125e3 - 11.017 * (T) + 0.049862 * pow((T), 2) - 7.7663e-5 * pow((T), 3) + 4.394e-8 * pow((T), 4))
#define NP_CP(T) (-531.43 + 7.135 * (T) - 0.011923 * pow((T), 2) + 9.3125e-6 * pow((T), 3) - 2.7679e-9 * pow((T), 4))
#define BASE_RHO(T) (1.4386e3 - 1.8711 * (T) + 2.737e-3 * pow((T), 2) - 2.3793e-6 * pow((T), 3))
#define NP_RHO 3970.0
#define VOL_FRAC 0.01

DEFINE_SPECIFIC_HEAT(my_user_cp, T, Tref, h, yi)
{
    real base_cp = 0.0;
    real np_cp = 0.0;
    real base_rho = 0.0;
    real np_rho = NP_RHO;
    real phi = VOL_FRAC;
    double cp_nf = 0.0;

    if (T < T_MIN) {
        base_cp = 1527.642017;
        //np_cp = NP_CP(T);
        base_rho = 1072.43701;
    }
    else if (T >= T_MIN && T <= T_MAX) {
        base_cp = BASE_CP(T);
        //np_cp = NP_CP(T);
        base_rho = BASE_RHO(T);
    }
    else if (T > T_MAX) {
        base_cp = 2748.034204;
        //np_cp = NP_CP(T);
        base_rho = 656.6955932;
    }

    cp_nf = ((1.0 - phi) * base_cp * base_rho + phi * NP_CP(T) * np_rho) / ((1.0 - phi) * base_rho + phi * np_rho);
    *h = cp_nf * (T - Tref);

    return cp_nf;
}
