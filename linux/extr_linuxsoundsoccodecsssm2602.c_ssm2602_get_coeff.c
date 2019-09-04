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
struct TYPE_3__ {int rate; int mclk; int srate; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* ssm2602_coeff_table ; 

__attribute__((used)) static inline int ssm2602_get_coeff(int mclk, int rate)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ssm2602_coeff_table); i++) {
		if (ssm2602_coeff_table[i].rate == rate &&
			ssm2602_coeff_table[i].mclk == mclk)
			return ssm2602_coeff_table[i].srate;
	}
	return -EINVAL;
}