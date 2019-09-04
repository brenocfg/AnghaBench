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
typedef  scalar_t__ u32 ;
typedef  int s32 ;

/* Variables and functions */
 int BIT (scalar_t__) ; 

s32 odm_sign_conversion(s32 value, u32 total_bit)
{
	if (value & BIT(total_bit - 1))
		value -= BIT(total_bit);
	return value;
}