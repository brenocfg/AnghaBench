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
#define  CS53L30_DEVID_AB 132 
#define  CS53L30_DEVID_CD 131 
#define  CS53L30_DEVID_E 130 
#define  CS53L30_IS 129 
#define  CS53L30_REVID 128 

__attribute__((used)) static bool cs53l30_writeable_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS53L30_DEVID_AB:
	case CS53L30_DEVID_CD:
	case CS53L30_DEVID_E:
	case CS53L30_REVID:
	case CS53L30_IS:
		return false;
	default:
		return true;
	}
}