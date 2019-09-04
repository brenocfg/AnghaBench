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
#define  FSL_SAI_RCR1 142 
#define  FSL_SAI_RCR2 141 
#define  FSL_SAI_RCR3 140 
#define  FSL_SAI_RCR4 139 
#define  FSL_SAI_RCR5 138 
#define  FSL_SAI_RCSR 137 
#define  FSL_SAI_RMR 136 
#define  FSL_SAI_TCR1 135 
#define  FSL_SAI_TCR2 134 
#define  FSL_SAI_TCR3 133 
#define  FSL_SAI_TCR4 132 
#define  FSL_SAI_TCR5 131 
#define  FSL_SAI_TCSR 130 
#define  FSL_SAI_TDR 129 
#define  FSL_SAI_TMR 128 

__attribute__((used)) static bool fsl_sai_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case FSL_SAI_TCSR:
	case FSL_SAI_TCR1:
	case FSL_SAI_TCR2:
	case FSL_SAI_TCR3:
	case FSL_SAI_TCR4:
	case FSL_SAI_TCR5:
	case FSL_SAI_TDR:
	case FSL_SAI_TMR:
	case FSL_SAI_RCSR:
	case FSL_SAI_RCR1:
	case FSL_SAI_RCR2:
	case FSL_SAI_RCR3:
	case FSL_SAI_RCR4:
	case FSL_SAI_RCR5:
	case FSL_SAI_RMR:
		return true;
	default:
		return false;
	}
}