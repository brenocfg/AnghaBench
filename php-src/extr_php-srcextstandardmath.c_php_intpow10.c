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
 double pow (double,double) ; 

__attribute__((used)) static inline double php_intpow10(int power) {
	static const double powers[] = {
		1e0,  1e1,  1e2,  1e3,  1e4,  1e5,  1e6,  1e7,
		1e8,  1e9,  1e10, 1e11, 1e12, 1e13, 1e14, 1e15,
		1e16, 1e17, 1e18, 1e19, 1e20, 1e21, 1e22};

	/* Not in lookup table */
	if (power < 0 || power > 22) {
		return pow(10.0, (double)power);
	}
	return powers[power];
}