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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct fsl_spdif_priv {struct regmap* regmap; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  REG_SPDIF_SCR ; 
 int SCR_SOFT_RESET ; 
 int /*<<< orphan*/  regcache_cache_bypass (struct regmap*,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (struct regmap*) ; 
 int /*<<< orphan*/  regcache_sync (struct regmap*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int spdif_softreset(struct fsl_spdif_priv *spdif_priv)
{
	struct regmap *regmap = spdif_priv->regmap;
	u32 val, cycle = 1000;

	regcache_cache_bypass(regmap, true);

	regmap_write(regmap, REG_SPDIF_SCR, SCR_SOFT_RESET);

	/*
	 * RESET bit would be cleared after finishing its reset procedure,
	 * which typically lasts 8 cycles. 1000 cycles will keep it safe.
	 */
	do {
		regmap_read(regmap, REG_SPDIF_SCR, &val);
	} while ((val & SCR_SOFT_RESET) && cycle--);

	regcache_cache_bypass(regmap, false);
	regcache_mark_dirty(regmap);
	regcache_sync(regmap);

	if (cycle)
		return 0;
	else
		return -EBUSY;
}