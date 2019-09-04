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
typedef  int u8 ;
typedef  int s8 ;

/* Variables and functions */

u8 rtl92e_evm_db_to_percent(s8 value)
{
	s8 ret_val;

	ret_val = value;

	if (ret_val >= 0)
		ret_val = 0;
	if (ret_val <= -33)
		ret_val = -33;
	ret_val = 0 - ret_val;
	ret_val *= 3;
	if (ret_val == 99)
		ret_val = 100;
	return ret_val;
}