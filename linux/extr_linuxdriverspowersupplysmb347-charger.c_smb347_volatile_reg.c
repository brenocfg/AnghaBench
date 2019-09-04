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
#define  IRQSTAT_A 135 
#define  IRQSTAT_C 134 
#define  IRQSTAT_E 133 
#define  IRQSTAT_F 132 
#define  STAT_A 131 
#define  STAT_B 130 
#define  STAT_C 129 
#define  STAT_E 128 

__attribute__((used)) static bool smb347_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case IRQSTAT_A:
	case IRQSTAT_C:
	case IRQSTAT_E:
	case IRQSTAT_F:
	case STAT_A:
	case STAT_B:
	case STAT_C:
	case STAT_E:
		return true;
	}

	return false;
}