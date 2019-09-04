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
 double fabs (double) ; 
 scalar_t__ floor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log10 (double) ; 

__attribute__((used)) static inline int php_intlog10abs(double value) {
	int result;
	value = fabs(value);

	if (value < 1e-8 || value > 1e22) {
		result = (int)floor(log10(value));
	} else {
		static const double values[] = {
			1e-8, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1,
			1e0,  1e1,  1e2,  1e3,  1e4,  1e5,  1e6,  1e7,
			1e8,  1e9,  1e10, 1e11, 1e12, 1e13, 1e14, 1e15,
			1e16, 1e17, 1e18, 1e19, 1e20, 1e21, 1e22};
		/* Do a binary search with 5 steps */
		result = 15;
		if (value < values[result]) {
			result -= 8;
		} else {
			result += 8;
		}
		if (value < values[result]) {
			result -= 4;
		} else {
			result += 4;
		}
		if (value < values[result]) {
			result -= 2;
		} else {
			result += 2;
		}
		if (value < values[result]) {
			result -= 1;
		} else {
			result += 1;
		}
		if (value < values[result]) {
			result -= 1;
		}
		result -= 8;
	}
	return result;
}