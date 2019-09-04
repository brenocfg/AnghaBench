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

/* Variables and functions */

__attribute__((used)) static int clip_1d(int *x0, int *y0, int *x1, int *y1, int maxdim) {
	double m;      /* gradient of line */

	if (*x0 < 0) {  /* start of line is left of window */
		if(*x1 < 0) { /* as is the end, so the line never cuts the window */
			return 0;
		}
		m = (*y1 - *y0)/(double)(*x1 - *x0); /* calculate the slope of the line */
		/* adjust x0 to be on the left boundary (ie to be zero), and y0 to match */
		*y0 -= (int)(m * *x0);
		*x0 = 0;
		/* now, perhaps, adjust the far end of the line as well */
		if (*x1 > maxdim) {
			*y1 += (int)(m * (maxdim - *x1));
			*x1 = maxdim;
		}
		return 1;
	}
	if (*x0 > maxdim) { /* start of line is right of window - complement of above */
		if (*x1 > maxdim) { /* as is the end, so the line misses the window */
			return 0;
		}
		m = (*y1 - *y0)/(double)(*x1 - *x0);  /* calculate the slope of the line */
		*y0 += (int)(m * (maxdim - *x0)); /* adjust so point is on the right boundary */
		*x0 = maxdim;
		/* now, perhaps, adjust the end of the line */
		if (*x1 < 0) {
			*y1 -= (int)(m * *x1);
			*x1 = 0;
		}
		return 1;
	}
	/* the final case - the start of the line is inside the window */
	if (*x1 > maxdim) { /* other end is outside to the right */
		m = (*y1 - *y0)/(double)(*x1 - *x0);  /* calculate the slope of the line */
		*y1 += (int)(m * (maxdim - *x1));
		*x1 = maxdim;
		return 1;
	}
	if (*x1 < 0) { /* other end is outside to the left */
		m = (*y1 - *y0)/(double)(*x1 - *x0);  /* calculate the slope of the line */
		*y1 -= (int)(m * *x1);
		*x1 = 0;
		return 1;
	}
	/* only get here if both points are inside the window */
	return 1;
}