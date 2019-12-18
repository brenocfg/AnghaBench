#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mclkx; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* cs53l30_mclkx_coeffs ; 

__attribute__((used)) static int cs53l30_get_mclkx_coeff(int mclkx)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(cs53l30_mclkx_coeffs); i++) {
		if (cs53l30_mclkx_coeffs[i].mclkx == mclkx)
			return i;
	}

	return -EINVAL;
}