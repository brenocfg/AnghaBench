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
struct device {int dummy; } ;

/* Variables and functions */
#define  NAU8822_REG_AGC_PEAK2PEAK 133 
#define  NAU8822_REG_AGC_PEAK_DETECT 132 
#define  NAU8822_REG_AUTOMUTE_CONTROL 131 
#define  NAU8822_REG_DEVICE_ID 130 
#define  NAU8822_REG_DEVICE_REVISION 129 
#define  NAU8822_REG_RESET 128 

__attribute__((used)) static bool nau8822_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case NAU8822_REG_RESET:
	case NAU8822_REG_DEVICE_REVISION:
	case NAU8822_REG_DEVICE_ID:
	case NAU8822_REG_AGC_PEAK2PEAK:
	case NAU8822_REG_AGC_PEAK_DETECT:
	case NAU8822_REG_AUTOMUTE_CONTROL:
		return true;
	default:
		return false;
	}
}