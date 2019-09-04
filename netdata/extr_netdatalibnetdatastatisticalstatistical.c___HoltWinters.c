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
typedef  int LONG_DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int*,int const) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __HoltWinters(
        const LONG_DOUBLE *series,
        int          entries,      // start_time + h

        LONG_DOUBLE alpha,        // alpha parameter of Holt-Winters Filter.
        LONG_DOUBLE beta,         // beta  parameter of Holt-Winters Filter. If set to 0, the function will do exponential smoothing.
        LONG_DOUBLE gamma,        // gamma parameter used for the seasonal component. If set to 0, an non-seasonal model is fitted.

        const int *seasonal,
        const int *period,
        const LONG_DOUBLE *a,      // Start value for level (a[0]).
        const LONG_DOUBLE *b,      // Start value for trend (b[0]).
        LONG_DOUBLE *s,            // Vector of start values for the seasonal component (s_1[0] ... s_p[0])

        /* return values */
        LONG_DOUBLE *SSE,          // The final sum of squared errors achieved in optimizing
        LONG_DOUBLE *level,        // Estimated values for the level component (size entries - t + 2)
        LONG_DOUBLE *trend,        // Estimated values for the trend component (size entries - t + 2)
        LONG_DOUBLE *season        // Estimated values for the seasonal component (size entries - t + 2)
)
{
    if(unlikely(entries < 4))
        return 0;

    int start_time = 2;

    LONG_DOUBLE res = 0, xhat = 0, stmp = 0;
    int i, i0, s0;

    /* copy start values to the beginning of the vectors */
    level[0] = *a;
    if(beta > 0) trend[0] = *b;
    if(gamma > 0) memcpy(season, s, *period * sizeof(LONG_DOUBLE));

    for(i = start_time - 1; i < entries; i++) {
        /* indices for period i */
        i0 = i - start_time + 2;
        s0 = i0 + *period - 1;

        /* forecast *for* period i */
        xhat = level[i0 - 1] + (beta > 0 ? trend[i0 - 1] : 0);
        stmp = gamma > 0 ? season[s0 - *period] : (*seasonal != 1);
        if (*seasonal == 1)
            xhat += stmp;
        else
            xhat *= stmp;

        /* Sum of Squared Errors */
        res   = series[i] - xhat;
        *SSE += res * res;

        /* estimate of level *in* period i */
        if (*seasonal == 1)
            level[i0] = alpha       * (series[i] - stmp)
                        + (1 - alpha) * (level[i0 - 1] + trend[i0 - 1]);
        else
            level[i0] = alpha       * (series[i] / stmp)
                        + (1 - alpha) * (level[i0 - 1] + trend[i0 - 1]);

        /* estimate of trend *in* period i */
        if (beta > 0)
            trend[i0] = beta        * (level[i0] - level[i0 - 1])
                        + (1 - beta)  * trend[i0 - 1];

        /* estimate of seasonal component *in* period i */
        if (gamma > 0) {
            if (*seasonal == 1)
                season[s0] = gamma       * (series[i] - level[i0])
                             + (1 - gamma) * stmp;
            else
                season[s0] = gamma       * (series[i] / level[i0])
                             + (1 - gamma) * stmp;
        }
    }

    return 1;
}