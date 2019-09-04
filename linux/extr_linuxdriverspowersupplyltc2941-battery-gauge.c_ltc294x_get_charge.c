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
struct ltc294x_info {scalar_t__ Qlsb; } ;
typedef  enum ltc294x_reg { ____Placeholder_ltc294x_reg } ltc294x_reg ;

/* Variables and functions */
 int convert_bin_to_uAh (struct ltc294x_info const*,int) ; 
 int ltc294x_read_charge_register (struct ltc294x_info const*,int) ; 

__attribute__((used)) static int ltc294x_get_charge(const struct ltc294x_info *info,
				enum ltc294x_reg reg, int *val)
{
	int value = ltc294x_read_charge_register(info, reg);

	if (value < 0)
		return value;
	/* When r_sense < 0, this counts up when the battery discharges */
	if (info->Qlsb < 0)
		value -= 0xFFFF;
	*val = convert_bin_to_uAh(info, value);
	return 0;
}