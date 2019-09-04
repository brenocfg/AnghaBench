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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct cs35l33_private {int /*<<< orphan*/  regmap; } ;
struct cs35l33_hg {int mem_depth; int hd_rm; int ldo_thld; int ldo_path_disable; int ldo_entry_delay; int vp_hg; int vp_hg_rate; int vp_hg_va; scalar_t__ vp_hg_auto; int /*<<< orphan*/  release_rate; scalar_t__ enable_hg_algo; } ;
struct cs35l33_pdata {struct cs35l33_hg hg_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int CS35L33_CLASS_HG_EN_MASK ; 
 int CS35L33_HD_RM_MASK ; 
 int CS35L33_HD_RM_SHIFT ; 
 int /*<<< orphan*/  CS35L33_HG_EN ; 
 int /*<<< orphan*/  CS35L33_HG_HEAD ; 
 int /*<<< orphan*/  CS35L33_HG_MEMLDO_CTL ; 
 int /*<<< orphan*/  CS35L33_HG_REL_RATE ; 
 int /*<<< orphan*/  CS35L33_LDO_DEL ; 
 int CS35L33_LDO_DISABLE_MASK ; 
 int CS35L33_LDO_DISABLE_SHIFT ; 
 int CS35L33_LDO_ENTRY_DELAY_MASK ; 
 int CS35L33_LDO_ENTRY_DELAY_SHIFT ; 
 int CS35L33_LDO_THLD_MASK ; 
 int CS35L33_LDO_THLD_SHIFT ; 
 int CS35L33_MEM_DEPTH_MASK ; 
 int CS35L33_MEM_DEPTH_SHIFT ; 
 int CS35L33_VP_HG_AUTO_MASK ; 
 int CS35L33_VP_HG_MASK ; 
 int CS35L33_VP_HG_RATE_MASK ; 
 int CS35L33_VP_HG_RATE_SHIFT ; 
 int CS35L33_VP_HG_SHIFT ; 
 int CS35L33_VP_HG_VA_MASK ; 
 int CS35L33_VP_HG_VA_SHIFT ; 
 int /*<<< orphan*/  cs35l33_vphg_auto_route ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct cs35l33_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs35l33_set_hg_data(struct snd_soc_component *component,
			       struct cs35l33_pdata *pdata)
{
	struct cs35l33_hg *hg_config = &pdata->hg_config;
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct cs35l33_private *priv = snd_soc_component_get_drvdata(component);

	if (hg_config->enable_hg_algo) {
		regmap_update_bits(priv->regmap, CS35L33_HG_MEMLDO_CTL,
			CS35L33_MEM_DEPTH_MASK,
			hg_config->mem_depth << CS35L33_MEM_DEPTH_SHIFT);
		regmap_write(priv->regmap, CS35L33_HG_REL_RATE,
			hg_config->release_rate);
		regmap_update_bits(priv->regmap, CS35L33_HG_HEAD,
			CS35L33_HD_RM_MASK,
			hg_config->hd_rm << CS35L33_HD_RM_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_HG_MEMLDO_CTL,
			CS35L33_LDO_THLD_MASK,
			hg_config->ldo_thld << CS35L33_LDO_THLD_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_HG_MEMLDO_CTL,
			CS35L33_LDO_DISABLE_MASK,
			hg_config->ldo_path_disable <<
				CS35L33_LDO_DISABLE_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_LDO_DEL,
			CS35L33_LDO_ENTRY_DELAY_MASK,
			hg_config->ldo_entry_delay <<
				CS35L33_LDO_ENTRY_DELAY_SHIFT);
		if (hg_config->vp_hg_auto) {
			regmap_update_bits(priv->regmap, CS35L33_HG_EN,
				CS35L33_VP_HG_AUTO_MASK,
				CS35L33_VP_HG_AUTO_MASK);
			snd_soc_dapm_add_routes(dapm, cs35l33_vphg_auto_route,
				ARRAY_SIZE(cs35l33_vphg_auto_route));
		}
		regmap_update_bits(priv->regmap, CS35L33_HG_EN,
			CS35L33_VP_HG_MASK,
			hg_config->vp_hg << CS35L33_VP_HG_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_LDO_DEL,
			CS35L33_VP_HG_RATE_MASK,
			hg_config->vp_hg_rate << CS35L33_VP_HG_RATE_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_LDO_DEL,
			CS35L33_VP_HG_VA_MASK,
			hg_config->vp_hg_va << CS35L33_VP_HG_VA_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_HG_EN,
			CS35L33_CLASS_HG_EN_MASK, CS35L33_CLASS_HG_EN_MASK);
	}
	return 0;
}