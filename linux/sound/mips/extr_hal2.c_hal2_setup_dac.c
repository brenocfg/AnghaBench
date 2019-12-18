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
struct hal2_pbus {unsigned int ctrl; int pbusnr; TYPE_1__* pbus; } ;
struct TYPE_4__ {int voices; struct hal2_pbus pbus; } ;
struct snd_hal2 {TYPE_2__ dac; } ;
struct TYPE_3__ {unsigned int pbdma_ctrl; } ;

/* Variables and functions */
 int H2I_C1_CLKID_SHIFT ; 
 int H2I_C1_DATAT_SHIFT ; 
 int H2I_C1_DMA_SHIFT ; 
 int /*<<< orphan*/  H2I_DAC_C1 ; 
 int /*<<< orphan*/  H2I_DMA_DRV ; 
 int /*<<< orphan*/  H2I_DMA_END ; 
 int /*<<< orphan*/  H2I_DMA_END_CODECTX ; 
 int /*<<< orphan*/  H2I_DMA_PORT_EN ; 
 int /*<<< orphan*/  H2I_DMA_PORT_EN_CODECTX ; 
 unsigned int HPC3_PDMACTRL_LD ; 
 unsigned int HPC3_PDMACTRL_RT ; 
 int /*<<< orphan*/  hal2_i_clearbit16 (struct snd_hal2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hal2_i_setbit16 (struct snd_hal2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hal2_i_write16 (struct snd_hal2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hal2_set_dac_rate (struct snd_hal2*) ; 

__attribute__((used)) static void hal2_setup_dac(struct snd_hal2 *hal2)
{
	unsigned int fifobeg, fifoend, highwater, sample_size;
	struct hal2_pbus *pbus = &hal2->dac.pbus;

	/* Now we set up some PBUS information. The PBUS needs information about
	 * what portion of the fifo it will use. If it's receiving or
	 * transmitting, and finally whether the stream is little endian or big
	 * endian. The information is written later, on the start call.
	 */
	sample_size = 2 * hal2->dac.voices;
	/* Fifo should be set to hold exactly four samples. Highwater mark
	 * should be set to two samples. */
	highwater = (sample_size * 2) >> 1;	/* halfwords */
	fifobeg = 0;				/* playback is first */
	fifoend = (sample_size * 4) >> 3;	/* doublewords */
	pbus->ctrl = HPC3_PDMACTRL_RT | HPC3_PDMACTRL_LD |
		     (highwater << 8) | (fifobeg << 16) | (fifoend << 24);
	/* We disable everything before we do anything at all */
	pbus->pbus->pbdma_ctrl = HPC3_PDMACTRL_LD;
	hal2_i_clearbit16(hal2, H2I_DMA_PORT_EN, H2I_DMA_PORT_EN_CODECTX);
	/* Setup the HAL2 for playback */
	hal2_set_dac_rate(hal2);
	/* Set endianess */
	hal2_i_clearbit16(hal2, H2I_DMA_END, H2I_DMA_END_CODECTX);
	/* Set DMA bus */
	hal2_i_setbit16(hal2, H2I_DMA_DRV, (1 << pbus->pbusnr));
	/* We are using 1st Bresenham clock generator for playback */
	hal2_i_write16(hal2, H2I_DAC_C1, (pbus->pbusnr << H2I_C1_DMA_SHIFT)
			| (1 << H2I_C1_CLKID_SHIFT)
			| (hal2->dac.voices << H2I_C1_DATAT_SHIFT));
}