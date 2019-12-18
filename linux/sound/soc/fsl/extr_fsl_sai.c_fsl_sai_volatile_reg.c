#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fsl_sai {TYPE_1__* soc_data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned int reg_offset; } ;

/* Variables and functions */
 unsigned int FSL_SAI_RCSR (unsigned int) ; 
#define  FSL_SAI_RDR0 151 
#define  FSL_SAI_RDR1 150 
#define  FSL_SAI_RDR2 149 
#define  FSL_SAI_RDR3 148 
#define  FSL_SAI_RDR4 147 
#define  FSL_SAI_RDR5 146 
#define  FSL_SAI_RDR6 145 
#define  FSL_SAI_RDR7 144 
#define  FSL_SAI_RFR0 143 
#define  FSL_SAI_RFR1 142 
#define  FSL_SAI_RFR2 141 
#define  FSL_SAI_RFR3 140 
#define  FSL_SAI_RFR4 139 
#define  FSL_SAI_RFR5 138 
#define  FSL_SAI_RFR6 137 
#define  FSL_SAI_RFR7 136 
 unsigned int FSL_SAI_TCSR (unsigned int) ; 
#define  FSL_SAI_TFR0 135 
#define  FSL_SAI_TFR1 134 
#define  FSL_SAI_TFR2 133 
#define  FSL_SAI_TFR3 132 
#define  FSL_SAI_TFR4 131 
#define  FSL_SAI_TFR5 130 
#define  FSL_SAI_TFR6 129 
#define  FSL_SAI_TFR7 128 
 struct fsl_sai* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static bool fsl_sai_volatile_reg(struct device *dev, unsigned int reg)
{
	struct fsl_sai *sai = dev_get_drvdata(dev);
	unsigned int ofs = sai->soc_data->reg_offset;

	if (reg == FSL_SAI_TCSR(ofs) || reg == FSL_SAI_RCSR(ofs))
		return true;

	switch (reg) {
	case FSL_SAI_TFR0:
	case FSL_SAI_TFR1:
	case FSL_SAI_TFR2:
	case FSL_SAI_TFR3:
	case FSL_SAI_TFR4:
	case FSL_SAI_TFR5:
	case FSL_SAI_TFR6:
	case FSL_SAI_TFR7:
	case FSL_SAI_RFR0:
	case FSL_SAI_RFR1:
	case FSL_SAI_RFR2:
	case FSL_SAI_RFR3:
	case FSL_SAI_RFR4:
	case FSL_SAI_RFR5:
	case FSL_SAI_RFR6:
	case FSL_SAI_RFR7:
	case FSL_SAI_RDR0:
	case FSL_SAI_RDR1:
	case FSL_SAI_RDR2:
	case FSL_SAI_RDR3:
	case FSL_SAI_RDR4:
	case FSL_SAI_RDR5:
	case FSL_SAI_RDR6:
	case FSL_SAI_RDR7:
		return true;
	default:
		return false;
	}
}