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
 unsigned int FSL_SAI_RCR5 (unsigned int) ; 
 unsigned int FSL_SAI_RCSR (unsigned int) ; 
#define  FSL_SAI_RMR 137 
 unsigned int FSL_SAI_TCR5 (unsigned int) ; 
 unsigned int FSL_SAI_TCSR (unsigned int) ; 
#define  FSL_SAI_TDR0 136 
#define  FSL_SAI_TDR1 135 
#define  FSL_SAI_TDR2 134 
#define  FSL_SAI_TDR3 133 
#define  FSL_SAI_TDR4 132 
#define  FSL_SAI_TDR5 131 
#define  FSL_SAI_TDR6 130 
#define  FSL_SAI_TDR7 129 
#define  FSL_SAI_TMR 128 
 struct fsl_sai* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static bool fsl_sai_writeable_reg(struct device *dev, unsigned int reg)
{
	struct fsl_sai *sai = dev_get_drvdata(dev);
	unsigned int ofs = sai->soc_data->reg_offset;

	if (reg >= FSL_SAI_TCSR(ofs) && reg <= FSL_SAI_TCR5(ofs))
		return true;

	if (reg >= FSL_SAI_RCSR(ofs) && reg <= FSL_SAI_RCR5(ofs))
		return true;

	switch (reg) {
	case FSL_SAI_TDR0:
	case FSL_SAI_TDR1:
	case FSL_SAI_TDR2:
	case FSL_SAI_TDR3:
	case FSL_SAI_TDR4:
	case FSL_SAI_TDR5:
	case FSL_SAI_TDR6:
	case FSL_SAI_TDR7:
	case FSL_SAI_TMR:
	case FSL_SAI_RMR:
		return true;
	default:
		return false;
	}
}