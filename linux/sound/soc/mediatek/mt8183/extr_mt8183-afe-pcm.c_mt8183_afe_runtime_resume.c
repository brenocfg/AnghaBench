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
struct mtk_base_afe {int /*<<< orphan*/  regmap; struct mt8183_afe_private* platform_priv; } ;
struct mt8183_afe_private {scalar_t__ pm_runtime_bypass_reg_ctl; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_CONN_24BIT ; 
 int /*<<< orphan*/  AFE_CONN_24BIT_1 ; 
 int /*<<< orphan*/  AFE_DAC_CON0 ; 
 int /*<<< orphan*/  AFE_MEMIF_MSB ; 
 int /*<<< orphan*/  AUDIO_TOP_CON0 ; 
 int CPU_HD_ALIGN_MASK_SFT ; 
 int CPU_HD_ALIGN_SFT ; 
 struct mtk_base_afe* dev_get_drvdata (struct device*) ; 
 int mt8183_afe_enable_clock (struct mtk_base_afe*) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt8183_afe_runtime_resume(struct device *dev)
{
	struct mtk_base_afe *afe = dev_get_drvdata(dev);
	struct mt8183_afe_private *afe_priv = afe->platform_priv;
	int ret;

	ret = mt8183_afe_enable_clock(afe);
	if (ret)
		return ret;

	if (!afe->regmap || afe_priv->pm_runtime_bypass_reg_ctl)
		goto skip_regmap;

	regcache_cache_only(afe->regmap, false);
	regcache_sync(afe->regmap);

	/* enable audio sys DCM for power saving */
	regmap_update_bits(afe->regmap, AUDIO_TOP_CON0, 0x1 << 29, 0x1 << 29);

	/* force cpu use 8_24 format when writing 32bit data */
	regmap_update_bits(afe->regmap, AFE_MEMIF_MSB,
			   CPU_HD_ALIGN_MASK_SFT, 0 << CPU_HD_ALIGN_SFT);

	/* set all output port to 24bit */
	regmap_write(afe->regmap, AFE_CONN_24BIT, 0xffffffff);
	regmap_write(afe->regmap, AFE_CONN_24BIT_1, 0xffffffff);

	/* enable AFE */
	regmap_update_bits(afe->regmap, AFE_DAC_CON0, 0x1, 0x1);

skip_regmap:
	return 0;
}