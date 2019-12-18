#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  double LONG_DOUBLE ;

/* Variables and functions */
 int __HoltWinters (double const*,int,double,double,double,int*,int*,double*,double*,double*,double*,double*,double*,double*) ; 
 double* callocz (size_t,int) ; 
 int /*<<< orphan*/  freez (double*) ; 
 int /*<<< orphan*/  isnan (double) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

LONG_DOUBLE holtwinters(const LONG_DOUBLE *series, size_t entries, LONG_DOUBLE alpha, LONG_DOUBLE beta, LONG_DOUBLE gamma, LONG_DOUBLE *forecast) {
    if(unlikely(isnan(alpha)))
        alpha = 0.3;

    if(unlikely(isnan(beta)))
        beta = 0.05;

    if(unlikely(isnan(gamma)))
        gamma = 0;

    int seasonal = 0;
    int period = 0;
    LONG_DOUBLE a0 = series[0];
    LONG_DOUBLE b0 = 0;
    LONG_DOUBLE s[] = {};

    LONG_DOUBLE errors = 0.0;
    size_t nb_computations = entries;
    LONG_DOUBLE *estimated_level  = callocz(nb_computations, sizeof(LONG_DOUBLE));
    LONG_DOUBLE *estimated_trend  = callocz(nb_computations, sizeof(LONG_DOUBLE));
    LONG_DOUBLE *estimated_season = callocz(nb_computations, sizeof(LONG_DOUBLE));

    int ret = __HoltWinters(
            series,
            (int)entries,
            alpha,
            beta,
            gamma,
            &seasonal,
            &period,
            &a0,
            &b0,
            s,
            &errors,
            estimated_level,
            estimated_trend,
            estimated_season
    );

    LONG_DOUBLE value = estimated_level[nb_computations - 1];

    if(forecast)
        *forecast = 0.0;

    freez(estimated_level);
    freez(estimated_trend);
    freez(estimated_season);

    if(!ret)
        return 0.0;

    return value;
}