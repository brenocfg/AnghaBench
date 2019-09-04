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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5677_priv {int type; int /*<<< orphan*/  regmap; int /*<<< orphan*/  fw2; int /*<<< orphan*/  fw1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SND_SOC_RT5677_SPI ; 
 int ENXIO ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
#define  RT5676 129 
#define  RT5677 128 
 scalar_t__ RT5677_BIAS_CUR4 ; 
 scalar_t__ RT5677_DIG_MISC ; 
 int RT5677_DSP_CLK_SRC_BYPASS ; 
 int RT5677_DSP_CLK_SRC_MASK ; 
 int /*<<< orphan*/  RT5677_FIRMWARE1 ; 
 int /*<<< orphan*/  RT5677_FIRMWARE2 ; 
 scalar_t__ RT5677_GLB_CLK1 ; 
 scalar_t__ RT5677_GLB_CLK2 ; 
 int RT5677_LDO1_SEL_MASK ; 
 int RT5677_MCLK2_SRC ; 
 int RT5677_MCLK_SRC_MASK ; 
 int RT5677_PLL2_PR_SRC_MASK ; 
 int RT5677_PLL2_PR_SRC_MCLK2 ; 
 scalar_t__ RT5677_PR_BASE ; 
 scalar_t__ RT5677_PWR_ANLG1 ; 
 scalar_t__ RT5677_PWR_ANLG2 ; 
 scalar_t__ RT5677_PWR_DSP1 ; 
 scalar_t__ RT5677_PWR_DSP2 ; 
 int RT5677_PWR_LDO1 ; 
 scalar_t__ RT5677_RESET ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int request_firmware (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt5677_set_dsp_mode (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  rt5677_spi_write_firmware (int,int /*<<< orphan*/ ) ; 
 struct rt5677_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5677_set_dsp_vad(struct snd_soc_component *component, bool on)
{
	struct rt5677_priv *rt5677 = snd_soc_component_get_drvdata(component);
	static bool activity;
	int ret;

	if (!IS_ENABLED(CONFIG_SND_SOC_RT5677_SPI))
		return -ENXIO;

	if (on && !activity) {
		activity = true;

		regcache_cache_only(rt5677->regmap, false);
		regcache_cache_bypass(rt5677->regmap, true);

		regmap_update_bits(rt5677->regmap, RT5677_DIG_MISC, 0x1, 0x1);
		regmap_update_bits(rt5677->regmap,
			RT5677_PR_BASE + RT5677_BIAS_CUR4, 0x0f00, 0x0f00);
		regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG1,
			RT5677_LDO1_SEL_MASK, 0x0);
		regmap_update_bits(rt5677->regmap, RT5677_PWR_ANLG2,
			RT5677_PWR_LDO1, RT5677_PWR_LDO1);
		switch (rt5677->type) {
		case RT5677:
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK1,
				RT5677_MCLK_SRC_MASK, RT5677_MCLK2_SRC);
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK2,
				RT5677_PLL2_PR_SRC_MASK |
				RT5677_DSP_CLK_SRC_MASK,
				RT5677_PLL2_PR_SRC_MCLK2 |
				RT5677_DSP_CLK_SRC_BYPASS);
			break;
		case RT5676:
			regmap_update_bits(rt5677->regmap, RT5677_GLB_CLK2,
				RT5677_DSP_CLK_SRC_MASK,
				RT5677_DSP_CLK_SRC_BYPASS);
			break;
		default:
			break;
		}
		regmap_write(rt5677->regmap, RT5677_PWR_DSP2, 0x07ff);
		regmap_write(rt5677->regmap, RT5677_PWR_DSP1, 0x07fd);
		rt5677_set_dsp_mode(component, true);

		ret = request_firmware(&rt5677->fw1, RT5677_FIRMWARE1,
			component->dev);
		if (ret == 0) {
			rt5677_spi_write_firmware(0x50000000, rt5677->fw1);
			release_firmware(rt5677->fw1);
		}

		ret = request_firmware(&rt5677->fw2, RT5677_FIRMWARE2,
			component->dev);
		if (ret == 0) {
			rt5677_spi_write_firmware(0x60000000, rt5677->fw2);
			release_firmware(rt5677->fw2);
		}

		regmap_update_bits(rt5677->regmap, RT5677_PWR_DSP1, 0x1, 0x0);

		regcache_cache_bypass(rt5677->regmap, false);
		regcache_cache_only(rt5677->regmap, true);
	} else if (!on && activity) {
		activity = false;

		regcache_cache_only(rt5677->regmap, false);
		regcache_cache_bypass(rt5677->regmap, true);

		regmap_update_bits(rt5677->regmap, RT5677_PWR_DSP1, 0x1, 0x1);
		rt5677_set_dsp_mode(component, false);
		regmap_write(rt5677->regmap, RT5677_PWR_DSP1, 0x0001);

		regmap_write(rt5677->regmap, RT5677_RESET, 0x10ec);

		regcache_cache_bypass(rt5677->regmap, false);
		regcache_mark_dirty(rt5677->regmap);
		regcache_sync(rt5677->regmap);
	}

	return 0;
}