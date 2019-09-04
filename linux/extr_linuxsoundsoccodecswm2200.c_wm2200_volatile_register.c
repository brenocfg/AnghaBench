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
#define  WM2200_ADPS1_IRQ0 134 
#define  WM2200_ADPS1_IRQ1 133 
#define  WM2200_DEVICE_REVISION 132 
#define  WM2200_INTERRUPT_RAW_STATUS_2 131 
#define  WM2200_INTERRUPT_STATUS_1 130 
#define  WM2200_INTERRUPT_STATUS_2 129 
#define  WM2200_SOFTWARE_RESET 128 
 TYPE_1__* wm2200_ranges ; 

__attribute__((used)) static bool wm2200_volatile_register(struct device *dev, unsigned int reg)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(wm2200_ranges); i++)
		if ((reg >= wm2200_ranges[i].window_start &&
		     reg <= wm2200_ranges[i].window_start +
		     wm2200_ranges[i].window_len) ||
		    (reg >= wm2200_ranges[i].range_min &&
		     reg <= wm2200_ranges[i].range_max))
			return true;

	switch (reg) {
	case WM2200_SOFTWARE_RESET:
	case WM2200_DEVICE_REVISION:
	case WM2200_ADPS1_IRQ0:
	case WM2200_ADPS1_IRQ1:
	case WM2200_INTERRUPT_STATUS_1:
	case WM2200_INTERRUPT_STATUS_2:
	case WM2200_INTERRUPT_RAW_STATUS_2:
		return true;
	default:
		return false;
	}
}