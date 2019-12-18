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
struct fsl_esai {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESAI_xFCR_xFR ; 
 int /*<<< orphan*/  REG_ESAI_RFCR ; 
 int /*<<< orphan*/  REG_ESAI_TFCR ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_esai_register_restore(struct fsl_esai *esai_priv)
{
	int ret;

	/* FIFO reset for safety */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TFCR,
			   ESAI_xFCR_xFR, ESAI_xFCR_xFR);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RFCR,
			   ESAI_xFCR_xFR, ESAI_xFCR_xFR);

	regcache_mark_dirty(esai_priv->regmap);
	ret = regcache_sync(esai_priv->regmap);
	if (ret)
		return ret;

	/* FIFO reset done */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TFCR, ESAI_xFCR_xFR, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RFCR, ESAI_xFCR_xFR, 0);

	return 0;
}