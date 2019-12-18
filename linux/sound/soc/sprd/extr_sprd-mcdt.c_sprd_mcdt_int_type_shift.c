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
typedef  int u32 ;
typedef  enum sprd_mcdt_fifo_int { ____Placeholder_sprd_mcdt_fifo_int } sprd_mcdt_fifo_int ;

/* Variables and functions */

__attribute__((used)) static u32 sprd_mcdt_int_type_shift(u8 channel,
				    enum sprd_mcdt_fifo_int int_type)
{
	switch (channel) {
	case 0:
	case 4:
	case 8:
		return int_type;

	case 1:
	case 5:
	case 9:
		return  8 + int_type;

	case 2:
	case 6:
		return 16 + int_type;

	case 3:
	case 7:
		return 24 + int_type;

	default:
		return 0;
	}
}