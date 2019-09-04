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
#define  MAX310X_IRQSTS_REG 131 
#define  MAX310X_RHR_REG 130 
#define  MAX310X_SPCHR_IRQSTS_REG 129 
#define  MAX310X_STS_IRQSTS_REG 128 

__attribute__((used)) static bool max310x_reg_precious(struct device *dev, unsigned int reg)
{
	switch (reg & 0x1f) {
	case MAX310X_RHR_REG:
	case MAX310X_IRQSTS_REG:
	case MAX310X_SPCHR_IRQSTS_REG:
	case MAX310X_STS_IRQSTS_REG:
		return true;
	default:
		break;
	}

	return false;
}