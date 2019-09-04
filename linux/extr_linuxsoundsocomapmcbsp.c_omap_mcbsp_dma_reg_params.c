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
struct omap_mcbsp {int phys_dma_base; TYPE_1__* pdata; } ;
struct TYPE_2__ {int reg_size; int reg_step; } ;

/* Variables and functions */
 int OMAP_MCBSP_REG_DRR ; 
 int OMAP_MCBSP_REG_DRR1 ; 
 int OMAP_MCBSP_REG_DXR ; 
 int OMAP_MCBSP_REG_DXR1 ; 

__attribute__((used)) static int omap_mcbsp_dma_reg_params(struct omap_mcbsp *mcbsp,
				     unsigned int stream)
{
	int data_reg;

	if (mcbsp->pdata->reg_size == 2) {
		if (stream)
			data_reg = OMAP_MCBSP_REG_DRR1;
		else
			data_reg = OMAP_MCBSP_REG_DXR1;
	} else {
		if (stream)
			data_reg = OMAP_MCBSP_REG_DRR;
		else
			data_reg = OMAP_MCBSP_REG_DXR;
	}

	return mcbsp->phys_dma_base + data_reg * mcbsp->pdata->reg_step;
}