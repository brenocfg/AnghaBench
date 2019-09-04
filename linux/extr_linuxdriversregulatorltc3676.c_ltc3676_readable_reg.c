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
#define  LTC3676_BUCK1 150 
#define  LTC3676_BUCK2 149 
#define  LTC3676_BUCK3 148 
#define  LTC3676_BUCK4 147 
#define  LTC3676_CLIRQ 146 
#define  LTC3676_CNTRL 145 
#define  LTC3676_DVB1A 144 
#define  LTC3676_DVB1B 143 
#define  LTC3676_DVB2A 142 
#define  LTC3676_DVB2B 141 
#define  LTC3676_DVB3A 140 
#define  LTC3676_DVB3B 139 
#define  LTC3676_DVB4A 138 
#define  LTC3676_DVB4B 137 
#define  LTC3676_HRST 136 
#define  LTC3676_IRQSTAT 135 
#define  LTC3676_LDOA 134 
#define  LTC3676_LDOB 133 
#define  LTC3676_MSKIRQ 132 
#define  LTC3676_MSKPG 131 
#define  LTC3676_SQD1 130 
#define  LTC3676_SQD2 129 
#define  LTC3676_USER 128 

__attribute__((used)) static bool ltc3676_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case LTC3676_IRQSTAT:
	case LTC3676_BUCK1:
	case LTC3676_BUCK2:
	case LTC3676_BUCK3:
	case LTC3676_BUCK4:
	case LTC3676_LDOA:
	case LTC3676_LDOB:
	case LTC3676_SQD1:
	case LTC3676_SQD2:
	case LTC3676_CNTRL:
	case LTC3676_DVB1A:
	case LTC3676_DVB1B:
	case LTC3676_DVB2A:
	case LTC3676_DVB2B:
	case LTC3676_DVB3A:
	case LTC3676_DVB3B:
	case LTC3676_DVB4A:
	case LTC3676_DVB4B:
	case LTC3676_MSKIRQ:
	case LTC3676_MSKPG:
	case LTC3676_USER:
	case LTC3676_HRST:
	case LTC3676_CLIRQ:
		return true;
	}
	return false;
}