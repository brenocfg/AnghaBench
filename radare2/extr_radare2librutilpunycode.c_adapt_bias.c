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
typedef  int ut32 ;

/* Variables and functions */
 int BASE ; 
 int DAMP ; 
 int SKEW ; 
 int TMAX ; 
 int TMIN ; 

ut32 adapt_bias(ut32 delta, unsigned n_points, int is_first) {
	ut32 k = 0;
	delta /= is_first? DAMP: 2;
	delta += delta / n_points;

	while (delta > ((BASE - TMIN) * TMAX) / 2) {
		delta /= (BASE - TMIN);
		k += BASE;
	}

	return k + (((BASE - TMIN + 1) * delta) / (delta + SKEW));
}