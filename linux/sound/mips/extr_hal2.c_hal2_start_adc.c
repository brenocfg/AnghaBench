#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hal2_pbus {int ctrl; TYPE_2__* pbus; } ;
struct TYPE_3__ {int /*<<< orphan*/  desc_dma; struct hal2_pbus pbus; } ;
struct snd_hal2 {TYPE_1__ adc; } ;
struct TYPE_4__ {int pbdma_ctrl; int /*<<< orphan*/  pbdma_dptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2I_DMA_PORT_EN ; 
 int /*<<< orphan*/  H2I_DMA_PORT_EN_CODECR ; 
 int HPC3_PDMACTRL_ACT ; 
 int /*<<< orphan*/  hal2_i_setbit16 (struct snd_hal2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hal2_start_adc(struct snd_hal2 *hal2)
{
	struct hal2_pbus *pbus = &hal2->adc.pbus;

	pbus->pbus->pbdma_dptr = hal2->adc.desc_dma;
	pbus->pbus->pbdma_ctrl = pbus->ctrl | HPC3_PDMACTRL_ACT;
	/* enable ADC */
	hal2_i_setbit16(hal2, H2I_DMA_PORT_EN, H2I_DMA_PORT_EN_CODECR);
}