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
#define  RT5660_EQ_CTRL1 135 
#define  RT5660_INT_IRQ_ST 134 
#define  RT5660_IRQ_CTRL2 133 
#define  RT5660_PRIV_DATA 132 
#define  RT5660_RESET 131 
#define  RT5660_VENDOR_ID 130 
#define  RT5660_VENDOR_ID1 129 
#define  RT5660_VENDOR_ID2 128 
 TYPE_1__* rt5660_ranges ; 

__attribute__((used)) static bool rt5660_volatile_register(struct device *dev, unsigned int reg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rt5660_ranges); i++)
		if ((reg >= rt5660_ranges[i].window_start &&
		     reg <= rt5660_ranges[i].window_start +
		     rt5660_ranges[i].window_len) ||
		    (reg >= rt5660_ranges[i].range_min &&
		     reg <= rt5660_ranges[i].range_max))
			return true;

	switch (reg) {
	case RT5660_RESET:
	case RT5660_PRIV_DATA:
	case RT5660_EQ_CTRL1:
	case RT5660_IRQ_CTRL2:
	case RT5660_INT_IRQ_ST:
	case RT5660_VENDOR_ID:
	case RT5660_VENDOR_ID1:
	case RT5660_VENDOR_ID2:
		return true;
	default:
		return false;
	}
}