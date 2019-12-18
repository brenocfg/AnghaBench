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
struct snd_soc_component {int dummy; } ;
struct monitor_cfg {int vmon_dpth; int vmon_loc; int vmon_frm; int imon_dpth; int imon_loc; int imon_frm; int imon_scale; int vpmon_dpth; int vpmon_loc; int vpmon_frm; int vbstmon_loc; int vbstmon_frm; int vpbrstat_dpth; int vpbrstat_loc; int vpbrstat_frm; int zerofill_dpth; int zerofill_loc; int zerofill_frm; scalar_t__ zerofill_specs; scalar_t__ vpbrstat_specs; scalar_t__ vbstmon_specs; scalar_t__ vpmon_specs; scalar_t__ imon_specs; scalar_t__ vmon_specs; scalar_t__ is_present; } ;
struct classh_cfg {int classh_bst_override; int classh_bst_max_limit; int classh_mem_depth; int classh_headroom; int classh_release_rate; int classh_wk_fet_disable; int classh_wk_fet_delay; int classh_wk_fet_thld; int classh_vpch_auto; int classh_vpch_rate; int classh_vpch_man; scalar_t__ classh_algo_enable; } ;
struct TYPE_2__ {int bst_vctl; int bst_ipk; int gain_zc; int aud_channel; int adv_channel; int sp_drv_str; int sp_drv_unused; scalar_t__ shared_bst; scalar_t__ stereo; int /*<<< orphan*/  boost_ind; struct monitor_cfg mon_cfg; struct classh_cfg classh_algo; } ;
struct cs35l35_private {int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS35L35_ADVIN_RXLOC_CTL ; 
 int /*<<< orphan*/  CS35L35_ADV_IN_LR_MASK ; 
 int CS35L35_ADV_IN_LR_SHIFT ; 
 int /*<<< orphan*/  CS35L35_AMP_GAIN_ZC_MASK ; 
 int CS35L35_AMP_GAIN_ZC_SHIFT ; 
 int /*<<< orphan*/  CS35L35_AUDIN_RXLOC_CTL ; 
 int /*<<< orphan*/  CS35L35_AUD_IN_LR_MASK ; 
 int CS35L35_AUD_IN_LR_SHIFT ; 
 int /*<<< orphan*/  CS35L35_BST_CTL_MASK ; 
 int /*<<< orphan*/  CS35L35_BST_CVTR_V_CTL ; 
 int /*<<< orphan*/  CS35L35_BST_IPK_MASK ; 
 int CS35L35_BST_IPK_SHIFT ; 
 int /*<<< orphan*/  CS35L35_BST_PEAK_I ; 
 int /*<<< orphan*/  CS35L35_CH_BST_LIM_MASK ; 
 int CS35L35_CH_BST_LIM_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_BST_OVR_MASK ; 
 int CS35L35_CH_BST_OVR_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_HDRM_CTL_MASK ; 
 int CS35L35_CH_HDRM_CTL_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_MEM_DEPTH_MASK ; 
 int CS35L35_CH_MEM_DEPTH_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_REL_RATE_MASK ; 
 int CS35L35_CH_REL_RATE_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_STEREO_MASK ; 
 int CS35L35_CH_STEREO_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_VP_AUTO_MASK ; 
 int CS35L35_CH_VP_AUTO_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_VP_MAN_MASK ; 
 int CS35L35_CH_VP_MAN_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_VP_RATE_MASK ; 
 int CS35L35_CH_VP_RATE_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_WKFET_DEL_MASK ; 
 int CS35L35_CH_WKFET_DEL_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_WKFET_DIS_MASK ; 
 int CS35L35_CH_WKFET_DIS_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CH_WKFET_THLD_MASK ; 
 int CS35L35_CH_WKFET_THLD_SHIFT ; 
 int /*<<< orphan*/  CS35L35_CLASS_H_CTL ; 
 int /*<<< orphan*/  CS35L35_CLASS_H_FET_DRIVE_CTL ; 
 int /*<<< orphan*/  CS35L35_CLASS_H_HEADRM_CTL ; 
 int /*<<< orphan*/  CS35L35_CLASS_H_RELEASE_RATE ; 
 int /*<<< orphan*/  CS35L35_CLASS_H_VP_CTL ; 
 int /*<<< orphan*/  CS35L35_CLK_CTL1 ; 
 int /*<<< orphan*/  CS35L35_IMON_DEPTH_MASK ; 
 int CS35L35_IMON_DEPTH_SHIFT ; 
 int /*<<< orphan*/  CS35L35_IMON_SCALE_CTL ; 
 int /*<<< orphan*/  CS35L35_IMON_SCALE_MASK ; 
 int CS35L35_IMON_SCALE_SHIFT ; 
 int /*<<< orphan*/  CS35L35_IMON_TXLOC_CTL ; 
 int /*<<< orphan*/  CS35L35_MON_FRM_MASK ; 
 int CS35L35_MON_FRM_SHIFT ; 
 int /*<<< orphan*/  CS35L35_MON_TXLOC_MASK ; 
 int CS35L35_MON_TXLOC_SHIFT ; 
 int /*<<< orphan*/  CS35L35_PROTECT_CTL ; 
 int /*<<< orphan*/  CS35L35_SPKMON_DEPTH_CTL ; 
 int /*<<< orphan*/  CS35L35_SP_DRV_MASK ; 
 int CS35L35_SP_DRV_SHIFT ; 
 int /*<<< orphan*/  CS35L35_SP_FMT_CTL3 ; 
 int /*<<< orphan*/  CS35L35_SP_I2S_DRV_MASK ; 
 int CS35L35_SP_I2S_DRV_SHIFT ; 
 int /*<<< orphan*/  CS35L35_SUPMON_DEPTH_CTL ; 
 int /*<<< orphan*/  CS35L35_VBSTMON_DEPTH_MASK ; 
 int CS35L35_VBSTMON_DEPTH_SHIFT ; 
 int /*<<< orphan*/  CS35L35_VBSTMON_TXLOC_CTL ; 
 int /*<<< orphan*/  CS35L35_VMON_DEPTH_MASK ; 
 int CS35L35_VMON_DEPTH_SHIFT ; 
 int /*<<< orphan*/  CS35L35_VMON_TXLOC_CTL ; 
 int /*<<< orphan*/  CS35L35_VPBRSTAT_DEPTH_MASK ; 
 int CS35L35_VPBRSTAT_DEPTH_SHIFT ; 
 int /*<<< orphan*/  CS35L35_VPBR_STATUS_TXLOC_CTL ; 
 int /*<<< orphan*/  CS35L35_VPMON_DEPTH_MASK ; 
 int CS35L35_VPMON_DEPTH_SHIFT ; 
 int /*<<< orphan*/  CS35L35_VPMON_TXLOC_CTL ; 
 int /*<<< orphan*/  CS35L35_ZEROFILL_DEPTH_MASK ; 
 int CS35L35_ZEROFILL_DEPTH_SHIFT ; 
 int /*<<< orphan*/  CS35L35_ZERO_FILL_LOC_CTL ; 
 int /*<<< orphan*/  cs35l35_adv_controls ; 
 int cs35l35_boost_inductor (struct cs35l35_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs35l35_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l35_component_probe(struct snd_soc_component *component)
{
	struct cs35l35_private *cs35l35 = snd_soc_component_get_drvdata(component);
	struct classh_cfg *classh = &cs35l35->pdata.classh_algo;
	struct monitor_cfg *monitor_config = &cs35l35->pdata.mon_cfg;
	int ret;

	/* Set Platform Data */
	if (cs35l35->pdata.bst_vctl)
		regmap_update_bits(cs35l35->regmap, CS35L35_BST_CVTR_V_CTL,
				CS35L35_BST_CTL_MASK,
				cs35l35->pdata.bst_vctl);

	if (cs35l35->pdata.bst_ipk)
		regmap_update_bits(cs35l35->regmap, CS35L35_BST_PEAK_I,
				CS35L35_BST_IPK_MASK,
				cs35l35->pdata.bst_ipk <<
				CS35L35_BST_IPK_SHIFT);

	ret = cs35l35_boost_inductor(cs35l35, cs35l35->pdata.boost_ind);
	if (ret)
		return ret;

	if (cs35l35->pdata.gain_zc)
		regmap_update_bits(cs35l35->regmap, CS35L35_PROTECT_CTL,
				CS35L35_AMP_GAIN_ZC_MASK,
				cs35l35->pdata.gain_zc <<
				CS35L35_AMP_GAIN_ZC_SHIFT);

	if (cs35l35->pdata.aud_channel)
		regmap_update_bits(cs35l35->regmap,
				CS35L35_AUDIN_RXLOC_CTL,
				CS35L35_AUD_IN_LR_MASK,
				cs35l35->pdata.aud_channel <<
				CS35L35_AUD_IN_LR_SHIFT);

	if (cs35l35->pdata.stereo) {
		regmap_update_bits(cs35l35->regmap,
				CS35L35_ADVIN_RXLOC_CTL,
				CS35L35_ADV_IN_LR_MASK,
				cs35l35->pdata.adv_channel <<
				CS35L35_ADV_IN_LR_SHIFT);
		if (cs35l35->pdata.shared_bst)
			regmap_update_bits(cs35l35->regmap, CS35L35_CLASS_H_CTL,
					CS35L35_CH_STEREO_MASK,
					1 << CS35L35_CH_STEREO_SHIFT);
		ret = snd_soc_add_component_controls(component, cs35l35_adv_controls,
					ARRAY_SIZE(cs35l35_adv_controls));
		if (ret)
			return ret;
	}

	if (cs35l35->pdata.sp_drv_str)
		regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL1,
				CS35L35_SP_DRV_MASK,
				cs35l35->pdata.sp_drv_str <<
				CS35L35_SP_DRV_SHIFT);
	if (cs35l35->pdata.sp_drv_unused)
		regmap_update_bits(cs35l35->regmap, CS35L35_SP_FMT_CTL3,
				   CS35L35_SP_I2S_DRV_MASK,
				   cs35l35->pdata.sp_drv_unused <<
				   CS35L35_SP_I2S_DRV_SHIFT);

	if (classh->classh_algo_enable) {
		if (classh->classh_bst_override)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_CTL,
					CS35L35_CH_BST_OVR_MASK,
					classh->classh_bst_override <<
					CS35L35_CH_BST_OVR_SHIFT);
		if (classh->classh_bst_max_limit)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_CTL,
					CS35L35_CH_BST_LIM_MASK,
					classh->classh_bst_max_limit <<
					CS35L35_CH_BST_LIM_SHIFT);
		if (classh->classh_mem_depth)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_CTL,
					CS35L35_CH_MEM_DEPTH_MASK,
					classh->classh_mem_depth <<
					CS35L35_CH_MEM_DEPTH_SHIFT);
		if (classh->classh_headroom)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_HEADRM_CTL,
					CS35L35_CH_HDRM_CTL_MASK,
					classh->classh_headroom <<
					CS35L35_CH_HDRM_CTL_SHIFT);
		if (classh->classh_release_rate)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_RELEASE_RATE,
					CS35L35_CH_REL_RATE_MASK,
					classh->classh_release_rate <<
					CS35L35_CH_REL_RATE_SHIFT);
		if (classh->classh_wk_fet_disable)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_FET_DRIVE_CTL,
					CS35L35_CH_WKFET_DIS_MASK,
					classh->classh_wk_fet_disable <<
					CS35L35_CH_WKFET_DIS_SHIFT);
		if (classh->classh_wk_fet_delay)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_FET_DRIVE_CTL,
					CS35L35_CH_WKFET_DEL_MASK,
					classh->classh_wk_fet_delay <<
					CS35L35_CH_WKFET_DEL_SHIFT);
		if (classh->classh_wk_fet_thld)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_FET_DRIVE_CTL,
					CS35L35_CH_WKFET_THLD_MASK,
					classh->classh_wk_fet_thld <<
					CS35L35_CH_WKFET_THLD_SHIFT);
		if (classh->classh_vpch_auto)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_VP_CTL,
					CS35L35_CH_VP_AUTO_MASK,
					classh->classh_vpch_auto <<
					CS35L35_CH_VP_AUTO_SHIFT);
		if (classh->classh_vpch_rate)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_VP_CTL,
					CS35L35_CH_VP_RATE_MASK,
					classh->classh_vpch_rate <<
					CS35L35_CH_VP_RATE_SHIFT);
		if (classh->classh_vpch_man)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_VP_CTL,
					CS35L35_CH_VP_MAN_MASK,
					classh->classh_vpch_man <<
					CS35L35_CH_VP_MAN_SHIFT);
	}

	if (monitor_config->is_present) {
		if (monitor_config->vmon_specs) {
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SPKMON_DEPTH_CTL,
					CS35L35_VMON_DEPTH_MASK,
					monitor_config->vmon_dpth <<
					CS35L35_VMON_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VMON_TXLOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->vmon_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VMON_TXLOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->vmon_frm <<
					CS35L35_MON_FRM_SHIFT);
		}
		if (monitor_config->imon_specs) {
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SPKMON_DEPTH_CTL,
					CS35L35_IMON_DEPTH_MASK,
					monitor_config->imon_dpth <<
					CS35L35_IMON_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_IMON_TXLOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->imon_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_IMON_TXLOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->imon_frm <<
					CS35L35_MON_FRM_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_IMON_SCALE_CTL,
					CS35L35_IMON_SCALE_MASK,
					monitor_config->imon_scale <<
					CS35L35_IMON_SCALE_SHIFT);
		}
		if (monitor_config->vpmon_specs) {
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SUPMON_DEPTH_CTL,
					CS35L35_VPMON_DEPTH_MASK,
					monitor_config->vpmon_dpth <<
					CS35L35_VPMON_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VPMON_TXLOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->vpmon_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VPMON_TXLOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->vpmon_frm <<
					CS35L35_MON_FRM_SHIFT);
		}
		if (monitor_config->vbstmon_specs) {
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SUPMON_DEPTH_CTL,
					CS35L35_VBSTMON_DEPTH_MASK,
					monitor_config->vpmon_dpth <<
					CS35L35_VBSTMON_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VBSTMON_TXLOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->vbstmon_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VBSTMON_TXLOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->vbstmon_frm <<
					CS35L35_MON_FRM_SHIFT);
		}
		if (monitor_config->vpbrstat_specs) {
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SUPMON_DEPTH_CTL,
					CS35L35_VPBRSTAT_DEPTH_MASK,
					monitor_config->vpbrstat_dpth <<
					CS35L35_VPBRSTAT_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VPBR_STATUS_TXLOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->vpbrstat_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VPBR_STATUS_TXLOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->vpbrstat_frm <<
					CS35L35_MON_FRM_SHIFT);
		}
		if (monitor_config->zerofill_specs) {
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SUPMON_DEPTH_CTL,
					CS35L35_ZEROFILL_DEPTH_MASK,
					monitor_config->zerofill_dpth <<
					CS35L35_ZEROFILL_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_ZERO_FILL_LOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->zerofill_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_ZERO_FILL_LOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->zerofill_frm <<
					CS35L35_MON_FRM_SHIFT);
		}
	}

	return 0;
}