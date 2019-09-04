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
#define  REG_MAINCNT3 133 
#define  REG_RFSTATE 132 
#define  REG_RSSI 131 
#define  REG_SLPCAL0 130 
#define  REG_SLPCAL1 129 
#define  REG_SLPCAL2 128 

__attribute__((used)) static bool
mrf24j40_long_reg_volatile(struct device *dev, unsigned int reg)
{
	/* can be changed during runtime */
	switch (reg) {
	case REG_SLPCAL0:
	case REG_SLPCAL1:
	case REG_SLPCAL2:
	case REG_RFSTATE:
	case REG_RSSI:
	case REG_MAINCNT3:
		return true;
	default:
		return false;
	}
}