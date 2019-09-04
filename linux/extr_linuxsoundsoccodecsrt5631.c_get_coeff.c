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
struct TYPE_3__ {int mclk; int rate; int bclk; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* coeff_div ; 

__attribute__((used)) static int get_coeff(int mclk, int rate, int timesofbclk)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].mclk == mclk && coeff_div[i].rate == rate &&
			(coeff_div[i].bclk / coeff_div[i].rate) == timesofbclk)
			return i;
	}
	return -EINVAL;
}