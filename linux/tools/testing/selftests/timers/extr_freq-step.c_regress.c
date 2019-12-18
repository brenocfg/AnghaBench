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
struct sample {double time; double offset; } ;

/* Variables and functions */
 double fabs (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static void regress(struct sample *samples, int n, double *intercept,
		    double *slope, double *r_stddev, double *r_max)
{
	double x, y, r, x_sum, y_sum, xy_sum, x2_sum, r2_sum;
	int i;

	x_sum = 0.0, y_sum = 0.0, xy_sum = 0.0, x2_sum = 0.0;

	for (i = 0; i < n; i++) {
		x = samples[i].time;
		y = samples[i].offset;

		x_sum += x;
		y_sum += y;
		xy_sum += x * y;
		x2_sum += x * x;
	}

	*slope = (xy_sum - x_sum * y_sum / n) / (x2_sum - x_sum * x_sum / n);
	*intercept = (y_sum - *slope * x_sum) / n;

	*r_max = 0.0, r2_sum = 0.0;

	for (i = 0; i < n; i++) {
		x = samples[i].time;
		y = samples[i].offset;
		r = fabs(x * *slope + *intercept - y);
		if (*r_max < r)
			*r_max = r;
		r2_sum += r * r;
	}

	*r_stddev = sqrt(r2_sum / n);
}