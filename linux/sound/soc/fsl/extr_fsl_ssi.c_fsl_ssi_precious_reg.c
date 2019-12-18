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
#define  REG_SSI_SACADD 133 
#define  REG_SSI_SACDAT 132 
#define  REG_SSI_SATAG 131 
#define  REG_SSI_SISR 130 
#define  REG_SSI_SRX0 129 
#define  REG_SSI_SRX1 128 

__attribute__((used)) static bool fsl_ssi_precious_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_SSI_SRX0:
	case REG_SSI_SRX1:
	case REG_SSI_SISR:
	case REG_SSI_SACADD:
	case REG_SSI_SACDAT:
	case REG_SSI_SATAG:
		return true;
	default:
		return false;
	}
}