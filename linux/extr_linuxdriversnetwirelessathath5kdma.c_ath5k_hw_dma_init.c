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
struct ath5k_hw {scalar_t__ ah_version; int /*<<< orphan*/  ah_imr; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_DMASIZE_128B ; 
 int /*<<< orphan*/  AR5K_REG_WRITE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_RXCFG ; 
 int /*<<< orphan*/  AR5K_RXCFG_SDMAMW ; 
 int /*<<< orphan*/  AR5K_TXCFG ; 
 int /*<<< orphan*/  AR5K_TXCFG_SDMAMR ; 
 int /*<<< orphan*/  ath5k_hw_set_imr (struct ath5k_hw*,int /*<<< orphan*/ ) ; 

void
ath5k_hw_dma_init(struct ath5k_hw *ah)
{
	/*
	 * Set Rx/Tx DMA Configuration
	 *
	 * Set standard DMA size (128). Note that
	 * a DMA size of 512 causes rx overruns and tx errors
	 * on pci-e cards (tested on 5424 but since rx overruns
	 * also occur on 5416/5418 with madwifi we set 128
	 * for all PCI-E cards to be safe).
	 *
	 * XXX: need to check 5210 for this
	 * TODO: Check out tx trigger level, it's always 64 on dumps but I
	 * guess we can tweak it and see how it goes ;-)
	 */
	if (ah->ah_version != AR5K_AR5210) {
		AR5K_REG_WRITE_BITS(ah, AR5K_TXCFG,
			AR5K_TXCFG_SDMAMR, AR5K_DMASIZE_128B);
		AR5K_REG_WRITE_BITS(ah, AR5K_RXCFG,
			AR5K_RXCFG_SDMAMW, AR5K_DMASIZE_128B);
	}

	/* Pre-enable interrupts on 5211/5212*/
	if (ah->ah_version != AR5K_AR5210)
		ath5k_hw_set_imr(ah, ah->ah_imr);

}