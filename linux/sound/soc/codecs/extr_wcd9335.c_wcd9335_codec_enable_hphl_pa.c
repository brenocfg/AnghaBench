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
struct wcd9335_codec {int hph_mode; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  WCD9335_CDC_RX1_RX_PATH_CTL ; 
 int /*<<< orphan*/  WCD9335_CDC_RX1_RX_PATH_MIX_CTL ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PGA_MUTE_DISABLE ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PGA_MUTE_EN_MASK ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wcd9335_codec_hph_post_pa_config (struct wcd9335_codec*,int,int) ; 

__attribute__((used)) static int wcd9335_codec_enable_hphl_pa(struct snd_soc_dapm_widget *w,
				      struct snd_kcontrol *kc,
				      int event)
{
	struct snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	struct wcd9335_codec *wcd = dev_get_drvdata(comp->dev);
	int hph_mode = wcd->hph_mode;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		break;
	case SND_SOC_DAPM_POST_PMU:
		/*
		 * 7ms sleep is required after PA is enabled as per
		 * HW requirement
		 */
		usleep_range(7000, 7100);

		wcd9335_codec_hph_post_pa_config(wcd, hph_mode, event);
		snd_soc_component_update_bits(comp,
					WCD9335_CDC_RX1_RX_PATH_CTL,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_DISABLE);

		/* Remove mix path mute if it is enabled */
		if ((snd_soc_component_read32(comp,
					WCD9335_CDC_RX1_RX_PATH_MIX_CTL)) &
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK)
			snd_soc_component_update_bits(comp,
					    WCD9335_CDC_RX1_RX_PATH_MIX_CTL,
					    WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					    WCD9335_CDC_RX_PGA_MUTE_DISABLE);

		break;
	case SND_SOC_DAPM_PRE_PMD:
		wcd9335_codec_hph_post_pa_config(wcd, hph_mode, event);
		break;
	case SND_SOC_DAPM_POST_PMD:
		/* 5ms sleep is required after PA is disabled as per
		 * HW requirement
		 */
		usleep_range(5000, 5500);
		break;
	};

	return 0;
}