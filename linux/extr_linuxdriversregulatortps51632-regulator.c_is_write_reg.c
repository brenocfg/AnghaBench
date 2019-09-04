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
#define  TPS51632_DVFS_CONTROL_REG 133 
#define  TPS51632_POWER_STATE_REG 132 
#define  TPS51632_SLEW_REGS 131 
#define  TPS51632_VMAX_REG 130 
#define  TPS51632_VOLTAGE_BASE_REG 129 
#define  TPS51632_VOLTAGE_SELECT_REG 128 

__attribute__((used)) static bool is_write_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TPS51632_VOLTAGE_SELECT_REG:
	case TPS51632_VOLTAGE_BASE_REG:
	case TPS51632_VMAX_REG:
	case TPS51632_DVFS_CONTROL_REG:
	case TPS51632_POWER_STATE_REG:
	case TPS51632_SLEW_REGS:
		return true;
	default:
		return false;
	}
}