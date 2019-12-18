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
typedef  int u8 ;
struct sprd_mcdt_dev {int dummy; } ;
typedef  enum sprd_mcdt_dma_chan { ____Placeholder_sprd_mcdt_dma_chan } sprd_mcdt_dma_chan ;

/* Variables and functions */
 int /*<<< orphan*/  MCDT_DMA_CFG0 ; 
 int /*<<< orphan*/  MCDT_DMA_CH0_SEL_MASK ; 
 int MCDT_DMA_CH0_SEL_SHIFT ; 
 int /*<<< orphan*/  MCDT_DMA_CH1_SEL_MASK ; 
 int MCDT_DMA_CH1_SEL_SHIFT ; 
 int /*<<< orphan*/  MCDT_DMA_CH2_SEL_MASK ; 
 int MCDT_DMA_CH2_SEL_SHIFT ; 
 int /*<<< orphan*/  MCDT_DMA_CH3_SEL_MASK ; 
 int MCDT_DMA_CH3_SEL_SHIFT ; 
 int /*<<< orphan*/  MCDT_DMA_CH4_SEL_MASK ; 
 int MCDT_DMA_CH4_SEL_SHIFT ; 
#define  SPRD_MCDT_DMA_CH0 132 
#define  SPRD_MCDT_DMA_CH1 131 
#define  SPRD_MCDT_DMA_CH2 130 
#define  SPRD_MCDT_DMA_CH3 129 
#define  SPRD_MCDT_DMA_CH4 128 
 int /*<<< orphan*/  sprd_mcdt_update (struct sprd_mcdt_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sprd_mcdt_dac_dma_chn_select(struct sprd_mcdt_dev *mcdt, u8 channel,
					 enum sprd_mcdt_dma_chan dma_chan)
{
	switch (dma_chan) {
	case SPRD_MCDT_DMA_CH0:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channel << MCDT_DMA_CH0_SEL_SHIFT,
				 MCDT_DMA_CH0_SEL_MASK);
		break;

	case SPRD_MCDT_DMA_CH1:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channel << MCDT_DMA_CH1_SEL_SHIFT,
				 MCDT_DMA_CH1_SEL_MASK);
		break;

	case SPRD_MCDT_DMA_CH2:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channel << MCDT_DMA_CH2_SEL_SHIFT,
				 MCDT_DMA_CH2_SEL_MASK);
		break;

	case SPRD_MCDT_DMA_CH3:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channel << MCDT_DMA_CH3_SEL_SHIFT,
				 MCDT_DMA_CH3_SEL_MASK);
		break;

	case SPRD_MCDT_DMA_CH4:
		sprd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channel << MCDT_DMA_CH4_SEL_SHIFT,
				 MCDT_DMA_CH4_SEL_MASK);
		break;
	}
}