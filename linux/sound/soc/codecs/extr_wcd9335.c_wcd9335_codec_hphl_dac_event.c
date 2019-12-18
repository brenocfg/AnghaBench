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
typedef  int u8 ;
struct wcd9335_codec {int hph_mode; int /*<<< orphan*/  clsh_ctrl; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int CLS_H_HIFI ; 
 int CLS_H_LOHIFI ; 
 int CLS_H_LP ; 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  WCD9335_CDC_RX1_RX_PATH_SEC0 ; 
 int /*<<< orphan*/  WCD_CLSH_EVENT_POST_PA ; 
 int /*<<< orphan*/  WCD_CLSH_EVENT_PRE_DAC ; 
 int /*<<< orphan*/  WCD_CLSH_STATE_HPHL ; 
 int WCD_CLSH_STATE_HPHR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wcd9335_codec_hph_mode_config (struct snd_soc_component*,int,int) ; 
 int wcd_clsh_ctrl_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcd_clsh_ctrl_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wcd9335_codec_hphl_dac_event(struct snd_soc_dapm_widget *w,
					struct snd_kcontrol *kc,
					int event)
{
	struct snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	struct wcd9335_codec *wcd = dev_get_drvdata(comp->dev);
	int hph_mode = wcd->hph_mode;
	u8 dem_inp;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* Read DEM INP Select */
		dem_inp = snd_soc_component_read32(comp,
				WCD9335_CDC_RX1_RX_PATH_SEC0) & 0x03;
		if (((hph_mode == CLS_H_HIFI) || (hph_mode == CLS_H_LOHIFI) ||
				(hph_mode == CLS_H_LP)) && (dem_inp != 0x01)) {
			dev_err(comp->dev, "Incorrect DEM Input\n");
			return -EINVAL;
		}
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_PRE_DAC,
					WCD_CLSH_STATE_HPHL,
					((hph_mode == CLS_H_LOHIFI) ?
					 CLS_H_HIFI : hph_mode));

		wcd9335_codec_hph_mode_config(comp, event, hph_mode);

		break;
	case SND_SOC_DAPM_POST_PMU:
		usleep_range(1000, 1100);
		break;
	case SND_SOC_DAPM_PRE_PMD:
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* 1000us required as per HW requirement */
		usleep_range(1000, 1100);

		if (!(wcd_clsh_ctrl_get_state(wcd->clsh_ctrl) &
				WCD_CLSH_STATE_HPHR))
			wcd9335_codec_hph_mode_config(comp, event, hph_mode);

		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_POST_PA,
				WCD_CLSH_STATE_HPHL,
				((hph_mode == CLS_H_LOHIFI) ?
				 CLS_H_HIFI : hph_mode));
		break;
	};

	return 0;
}