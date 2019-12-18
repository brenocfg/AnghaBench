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
#define  MAX98504_GLOBAL_ENABLE 133 
#define  MAX98504_INTERRUPT_FLAGS 132 
#define  MAX98504_INTERRUPT_FLAG_CLEARS 131 
#define  MAX98504_INTERRUPT_STATUS 130 
#define  MAX98504_SOFTWARE_RESET 129 
#define  MAX98504_WATCHDOG_CLEAR 128 

__attribute__((used)) static bool max98504_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MAX98504_INTERRUPT_STATUS:
	case MAX98504_INTERRUPT_FLAGS:
	case MAX98504_INTERRUPT_FLAG_CLEARS:
	case MAX98504_WATCHDOG_CLEAR:
	case MAX98504_GLOBAL_ENABLE:
	case MAX98504_SOFTWARE_RESET:
		return true;
	default:
		return false;
	}
}