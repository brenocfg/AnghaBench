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
#define  ALC5632_EQ_CTRL 135 
#define  ALC5632_GPIO_PIN_STATUS 134 
#define  ALC5632_HID_CTRL_DATA 133 
#define  ALC5632_OVER_CURR_STATUS 132 
#define  ALC5632_PWR_DOWN_CTRL_STATUS 131 
#define  ALC5632_RESET 130 
#define  ALC5632_VENDOR_ID1 129 
#define  ALC5632_VENDOR_ID2 128 

__attribute__((used)) static bool alc5632_volatile_register(struct device *dev,
							unsigned int reg)
{
	switch (reg) {
	case ALC5632_RESET:
	case ALC5632_PWR_DOWN_CTRL_STATUS:
	case ALC5632_GPIO_PIN_STATUS:
	case ALC5632_OVER_CURR_STATUS:
	case ALC5632_HID_CTRL_DATA:
	case ALC5632_EQ_CTRL:
	case ALC5632_VENDOR_ID1:
	case ALC5632_VENDOR_ID2:
		return true;

	default:
		break;
	}

	return false;
}