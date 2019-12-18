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
struct stm32_spdifrx_data {int /*<<< orphan*/  lock; TYPE_1__* pdev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SPDIFRX_CR_CUMSK ; 
 int SPDIFRX_CR_PMSK ; 
 int SPDIFRX_CR_PTMSK ; 
 int SPDIFRX_CR_RXSTEO ; 
 int SPDIFRX_CR_SPDIFENSET (int /*<<< orphan*/ ) ; 
 int SPDIFRX_CR_SPDIFEN_MASK ; 
 int SPDIFRX_CR_VMSK ; 
 int SPDIFRX_CR_WFA ; 
 int SPDIFRX_IMR_IFEIE ; 
 int SPDIFRX_IMR_PERRIE ; 
 int SPDIFRX_IMR_SYNCDIE ; 
 int /*<<< orphan*/  SPDIFRX_SPDIFEN_SYNC ; 
 int /*<<< orphan*/  STM32_SPDIFRX_CR ; 
 int /*<<< orphan*/  STM32_SPDIFRX_IMR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_spdifrx_start_sync(struct stm32_spdifrx_data *spdifrx)
{
	int cr, cr_mask, imr, ret;

	/* Enable IRQs */
	imr = SPDIFRX_IMR_IFEIE | SPDIFRX_IMR_SYNCDIE | SPDIFRX_IMR_PERRIE;
	ret = regmap_update_bits(spdifrx->regmap, STM32_SPDIFRX_IMR, imr, imr);
	if (ret)
		return ret;

	spin_lock(&spdifrx->lock);

	spdifrx->refcount++;

	regmap_read(spdifrx->regmap, STM32_SPDIFRX_CR, &cr);

	if (!(cr & SPDIFRX_CR_SPDIFEN_MASK)) {
		/*
		 * Start sync if SPDIFRX is still in idle state.
		 * SPDIFRX reception enabled when sync done
		 */
		dev_dbg(&spdifrx->pdev->dev, "start synchronization\n");

		/*
		 * SPDIFRX configuration:
		 * Wait for activity before starting sync process. This avoid
		 * to issue sync errors when spdif signal is missing on input.
		 * Preamble, CS, user, validity and parity error bits not copied
		 * to DR register.
		 */
		cr = SPDIFRX_CR_WFA | SPDIFRX_CR_PMSK | SPDIFRX_CR_VMSK |
		     SPDIFRX_CR_CUMSK | SPDIFRX_CR_PTMSK | SPDIFRX_CR_RXSTEO;
		cr_mask = cr;

		cr |= SPDIFRX_CR_SPDIFENSET(SPDIFRX_SPDIFEN_SYNC);
		cr_mask |= SPDIFRX_CR_SPDIFEN_MASK;
		ret = regmap_update_bits(spdifrx->regmap, STM32_SPDIFRX_CR,
					 cr_mask, cr);
		if (ret < 0)
			dev_err(&spdifrx->pdev->dev,
				"Failed to start synchronization\n");
	}

	spin_unlock(&spdifrx->lock);

	return ret;
}