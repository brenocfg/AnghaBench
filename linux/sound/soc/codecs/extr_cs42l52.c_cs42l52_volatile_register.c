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
#define  CS42L52_BATT_LEVEL 132 
#define  CS42L52_CHARGE_PUMP 131 
#define  CS42L52_CLK_STATUS 130 
#define  CS42L52_IFACE_CTL2 129 
#define  CS42L52_SPK_STATUS 128 

__attribute__((used)) static bool cs42l52_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS42L52_IFACE_CTL2:
	case CS42L52_CLK_STATUS:
	case CS42L52_BATT_LEVEL:
	case CS42L52_SPK_STATUS:
	case CS42L52_CHARGE_PUMP:
		return true;
	default:
		return false;
	}
}