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
#define  REG_SSI_SACADD 139 
#define  REG_SSI_SACCST 138 
#define  REG_SSI_SACDAT 137 
#define  REG_SSI_SACNT 136 
#define  REG_SSI_SATAG 135 
#define  REG_SSI_SFCSR 134 
#define  REG_SSI_SISR 133 
#define  REG_SSI_SOR 132 
#define  REG_SSI_SRX0 131 
#define  REG_SSI_SRX1 130 
#define  REG_SSI_STX0 129 
#define  REG_SSI_STX1 128 

__attribute__((used)) static bool fsl_ssi_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_SSI_STX0:
	case REG_SSI_STX1:
	case REG_SSI_SRX0:
	case REG_SSI_SRX1:
	case REG_SSI_SISR:
	case REG_SSI_SFCSR:
	case REG_SSI_SACNT:
	case REG_SSI_SACADD:
	case REG_SSI_SACDAT:
	case REG_SSI_SATAG:
	case REG_SSI_SACCST:
	case REG_SSI_SOR:
		return true;
	default:
		return false;
	}
}