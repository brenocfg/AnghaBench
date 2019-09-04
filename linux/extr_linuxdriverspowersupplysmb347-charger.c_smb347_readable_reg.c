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
#define  CFG_ADDRESS 143 
#define  CFG_CHARGE_CURRENT 142 
#define  CFG_CURRENT_LIMIT 141 
#define  CFG_FAULT_IRQ 140 
#define  CFG_FLOAT_VOLTAGE 139 
#define  CFG_OTG 138 
#define  CFG_OTHER 137 
#define  CFG_PIN 136 
#define  CFG_STAT 135 
#define  CFG_STATUS_IRQ 134 
#define  CFG_SYSOK 133 
#define  CFG_TEMP_LIMIT 132 
#define  CFG_THERM 131 
#define  CMD_A 130 
#define  CMD_B 129 
#define  CMD_C 128 
 int smb347_volatile_reg (struct device*,unsigned int) ; 

__attribute__((used)) static bool smb347_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CFG_CHARGE_CURRENT:
	case CFG_CURRENT_LIMIT:
	case CFG_FLOAT_VOLTAGE:
	case CFG_STAT:
	case CFG_PIN:
	case CFG_THERM:
	case CFG_SYSOK:
	case CFG_OTHER:
	case CFG_OTG:
	case CFG_TEMP_LIMIT:
	case CFG_FAULT_IRQ:
	case CFG_STATUS_IRQ:
	case CFG_ADDRESS:
	case CMD_A:
	case CMD_B:
	case CMD_C:
		return true;
	}

	return smb347_volatile_reg(dev, reg);
}