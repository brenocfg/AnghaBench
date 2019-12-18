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
struct device {int dummy; } ;
struct TYPE_3__ {unsigned int window_start; unsigned int window_len; unsigned int range_min; unsigned int range_max; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
#define  RT5651_ALC_1 137 
#define  RT5651_DEVICE_ID 136 
#define  RT5651_EQ_CTRL1 135 
#define  RT5651_INT_IRQ_ST 134 
#define  RT5651_IRQ_CTRL2 133 
#define  RT5651_PGM_REG_ARR1 132 
#define  RT5651_PGM_REG_ARR3 131 
#define  RT5651_PRIV_DATA 130 
#define  RT5651_RESET 129 
#define  RT5651_VENDOR_ID 128 
 TYPE_1__* rt5651_ranges ; 

__attribute__((used)) static bool rt5651_volatile_register(struct device *dev,  unsigned int reg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rt5651_ranges); i++) {
		if ((reg >= rt5651_ranges[i].window_start &&
		     reg <= rt5651_ranges[i].window_start +
		     rt5651_ranges[i].window_len) ||
		    (reg >= rt5651_ranges[i].range_min &&
		     reg <= rt5651_ranges[i].range_max)) {
			return true;
		}
	}

	switch (reg) {
	case RT5651_RESET:
	case RT5651_PRIV_DATA:
	case RT5651_EQ_CTRL1:
	case RT5651_ALC_1:
	case RT5651_IRQ_CTRL2:
	case RT5651_INT_IRQ_ST:
	case RT5651_PGM_REG_ARR1:
	case RT5651_PGM_REG_ARR3:
	case RT5651_VENDOR_ID:
	case RT5651_DEVICE_ID:
		return true;
	default:
		return false;
	}
}