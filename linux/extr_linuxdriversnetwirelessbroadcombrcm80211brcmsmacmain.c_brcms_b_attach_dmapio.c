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
typedef  int uint ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_hardware {int unit; int** txavail; TYPE_1__* band; int /*<<< orphan*/ ** di; int /*<<< orphan*/  d11core; } ;
struct brcms_c_info {struct brcms_hardware* hw; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/  mhfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_HWRXOFF ; 
 int /*<<< orphan*/  DMA_RX ; 
 int /*<<< orphan*/  DMA_TX ; 
 int NFIFO ; 
 int /*<<< orphan*/  NRXBUFPOST ; 
 int /*<<< orphan*/  NRXD ; 
 int /*<<< orphan*/  NTXD ; 
 int /*<<< orphan*/  RXBUFSZ ; 
 int /*<<< orphan*/  brcms_c_mhfdef (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_err (int /*<<< orphan*/ ,char*,int) ; 
 void* dma_attach (char*,struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_getvar (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dmareg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static bool brcms_b_attach_dmapio(struct brcms_c_info *wlc, uint j, bool wme)
{
	uint i;
	char name[8];
	/*
	 * ucode host flag 2 needed for pio mode, independent of band and fifo
	 */
	u16 pio_mhf2 = 0;
	struct brcms_hardware *wlc_hw = wlc->hw;
	uint unit = wlc_hw->unit;

	/* name and offsets for dma_attach */
	snprintf(name, sizeof(name), "wl%d", unit);

	if (wlc_hw->di[0] == NULL) {	/* Init FIFOs */
		int dma_attach_err = 0;

		/*
		 * FIFO 0
		 * TX: TX_AC_BK_FIFO (TX AC Background data packets)
		 * RX: RX_FIFO (RX data packets)
		 */
		wlc_hw->di[0] = dma_attach(name, wlc,
					   (wme ? dmareg(DMA_TX, 0) : 0),
					   dmareg(DMA_RX, 0),
					   (wme ? NTXD : 0), NRXD,
					   RXBUFSZ, -1, NRXBUFPOST,
					   BRCMS_HWRXOFF);
		dma_attach_err |= (NULL == wlc_hw->di[0]);

		/*
		 * FIFO 1
		 * TX: TX_AC_BE_FIFO (TX AC Best-Effort data packets)
		 *   (legacy) TX_DATA_FIFO (TX data packets)
		 * RX: UNUSED
		 */
		wlc_hw->di[1] = dma_attach(name, wlc,
					   dmareg(DMA_TX, 1), 0,
					   NTXD, 0, 0, -1, 0, 0);
		dma_attach_err |= (NULL == wlc_hw->di[1]);

		/*
		 * FIFO 2
		 * TX: TX_AC_VI_FIFO (TX AC Video data packets)
		 * RX: UNUSED
		 */
		wlc_hw->di[2] = dma_attach(name, wlc,
					   dmareg(DMA_TX, 2), 0,
					   NTXD, 0, 0, -1, 0, 0);
		dma_attach_err |= (NULL == wlc_hw->di[2]);
		/*
		 * FIFO 3
		 * TX: TX_AC_VO_FIFO (TX AC Voice data packets)
		 *   (legacy) TX_CTL_FIFO (TX control & mgmt packets)
		 */
		wlc_hw->di[3] = dma_attach(name, wlc,
					   dmareg(DMA_TX, 3),
					   0, NTXD, 0, 0, -1,
					   0, 0);
		dma_attach_err |= (NULL == wlc_hw->di[3]);
/* Cleaner to leave this as if with AP defined */

		if (dma_attach_err) {
			brcms_err(wlc_hw->d11core,
				  "wl%d: wlc_attach: dma_attach failed\n",
				  unit);
			return false;
		}

		/* get pointer to dma engine tx flow control variable */
		for (i = 0; i < NFIFO; i++)
			if (wlc_hw->di[i])
				wlc_hw->txavail[i] =
				    (uint *) dma_getvar(wlc_hw->di[i],
							"&txavail");
	}

	/* initial ucode host flags */
	brcms_c_mhfdef(wlc, wlc_hw->band->mhfs, pio_mhf2);

	return true;
}