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
#define  FSL_SAI_RCSR 132 
#define  FSL_SAI_RDR 131 
#define  FSL_SAI_RFR 130 
#define  FSL_SAI_TCSR 129 
#define  FSL_SAI_TFR 128 

__attribute__((used)) static bool fsl_sai_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case FSL_SAI_TCSR:
	case FSL_SAI_RCSR:
	case FSL_SAI_TFR:
	case FSL_SAI_RFR:
	case FSL_SAI_RDR:
		return true;
	default:
		return false;
	}
}