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
#define  M98090_REG_DEVICE_STATUS 131 
#define  M98090_REG_JACK_STATUS 130 
#define  M98090_REG_REVISION_ID 129 
#define  M98090_REG_SOFTWARE_RESET 128 

__attribute__((used)) static bool max98090_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case M98090_REG_SOFTWARE_RESET:
	case M98090_REG_DEVICE_STATUS:
	case M98090_REG_JACK_STATUS:
	case M98090_REG_REVISION_ID:
		return true;
	default:
		return false;
	}
}