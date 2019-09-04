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
struct stm32_spdifrx_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; scalar_t__ refcount; } ;

/* Variables and functions */
 int SPDIFRX_CR_RXDMAEN ; 
 int SPDIFRX_CR_SPDIFENSET (int /*<<< orphan*/ ) ; 
 int SPDIFRX_CR_SPDIFEN_MASK ; 
 int /*<<< orphan*/  SPDIFRX_SPDIFEN_DISABLE ; 
 int SPDIFRX_XIFCR_MASK ; 
 int SPDIFRX_XIMR_MASK ; 
 int /*<<< orphan*/  STM32_SPDIFRX_CR ; 
 int /*<<< orphan*/  STM32_SPDIFRX_CSR ; 
 int /*<<< orphan*/  STM32_SPDIFRX_DR ; 
 int /*<<< orphan*/  STM32_SPDIFRX_IFCR ; 
 int /*<<< orphan*/  STM32_SPDIFRX_IMR ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stm32_spdifrx_stop(struct stm32_spdifrx_data *spdifrx)
{
	int cr, cr_mask, reg;

	spin_lock(&spdifrx->lock);

	if (--spdifrx->refcount) {
		spin_unlock(&spdifrx->lock);
		return;
	}

	cr = SPDIFRX_CR_SPDIFENSET(SPDIFRX_SPDIFEN_DISABLE);
	cr_mask = SPDIFRX_CR_SPDIFEN_MASK | SPDIFRX_CR_RXDMAEN;

	regmap_update_bits(spdifrx->regmap, STM32_SPDIFRX_CR, cr_mask, cr);

	regmap_update_bits(spdifrx->regmap, STM32_SPDIFRX_IMR,
			   SPDIFRX_XIMR_MASK, 0);

	regmap_update_bits(spdifrx->regmap, STM32_SPDIFRX_IFCR,
			   SPDIFRX_XIFCR_MASK, SPDIFRX_XIFCR_MASK);

	/* dummy read to clear CSRNE and RXNE in status register */
	regmap_read(spdifrx->regmap, STM32_SPDIFRX_DR, &reg);
	regmap_read(spdifrx->regmap, STM32_SPDIFRX_CSR, &reg);

	spin_unlock(&spdifrx->lock);
}