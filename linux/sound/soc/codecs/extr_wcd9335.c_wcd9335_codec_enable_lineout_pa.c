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
struct snd_soc_dapm_widget {scalar_t__ reg; int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 scalar_t__ WCD9335_ANA_LO_1_2 ; 
 scalar_t__ WCD9335_ANA_LO_3_4 ; 
 int WCD9335_CDC_RX3_RX_PATH_CTL ; 
 int WCD9335_CDC_RX3_RX_PATH_MIX_CTL ; 
 int WCD9335_CDC_RX4_RX_PATH_CTL ; 
 int WCD9335_CDC_RX4_RX_PATH_MIX_CTL ; 
 int WCD9335_CDC_RX5_RX_PATH_CTL ; 
 int WCD9335_CDC_RX5_RX_PATH_MIX_CTL ; 
 int WCD9335_CDC_RX6_RX_PATH_CTL ; 
 int WCD9335_CDC_RX6_RX_PATH_MIX_CTL ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PGA_MUTE_DISABLE ; 
 int /*<<< orphan*/  WCD9335_CDC_RX_PGA_MUTE_EN_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int wcd9335_codec_enable_lineout_pa(struct snd_soc_dapm_widget *w,
					 struct snd_kcontrol *kc,
					 int event)
{
	struct snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	int vol_reg = 0, mix_vol_reg = 0;

	if (w->reg == WCD9335_ANA_LO_1_2) {
		if (w->shift == 7) {
			vol_reg = WCD9335_CDC_RX3_RX_PATH_CTL;
			mix_vol_reg = WCD9335_CDC_RX3_RX_PATH_MIX_CTL;
		} else if (w->shift == 6) {
			vol_reg = WCD9335_CDC_RX4_RX_PATH_CTL;
			mix_vol_reg = WCD9335_CDC_RX4_RX_PATH_MIX_CTL;
		}
	} else if (w->reg == WCD9335_ANA_LO_3_4) {
		if (w->shift == 7) {
			vol_reg = WCD9335_CDC_RX5_RX_PATH_CTL;
			mix_vol_reg = WCD9335_CDC_RX5_RX_PATH_MIX_CTL;
		} else if (w->shift == 6) {
			vol_reg = WCD9335_CDC_RX6_RX_PATH_CTL;
			mix_vol_reg = WCD9335_CDC_RX6_RX_PATH_MIX_CTL;
		}
	} else {
		dev_err(comp->dev, "Error enabling lineout PA\n");
		return -EINVAL;
	}

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* 5ms sleep is required after PA is enabled as per
		 * HW requirement
		 */
		usleep_range(5000, 5500);
		snd_soc_component_update_bits(comp, vol_reg,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_DISABLE);

		/* Remove mix path mute if it is enabled */
		if ((snd_soc_component_read32(comp, mix_vol_reg)) &
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK)
			snd_soc_component_update_bits(comp,  mix_vol_reg,
					WCD9335_CDC_RX_PGA_MUTE_EN_MASK,
					WCD9335_CDC_RX_PGA_MUTE_DISABLE);
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