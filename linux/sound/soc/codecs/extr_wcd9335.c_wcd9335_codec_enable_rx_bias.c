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
struct wcd9335_codec {int rx_bias_count; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  WCD9335_ANA_RX_BIAS_DISABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_RX_BIAS_ENABLE ; 
 int /*<<< orphan*/  WCD9335_ANA_RX_BIAS_ENABLE_MASK ; 
 int /*<<< orphan*/  WCD9335_ANA_RX_SUPPLIES ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcd9335_codec_init_flyback (struct snd_soc_component*) ; 

__attribute__((used)) static int wcd9335_codec_enable_rx_bias(struct snd_soc_dapm_widget *w,
		struct snd_kcontrol *kc, int event)
{
	struct snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	struct wcd9335_codec *wcd = dev_get_drvdata(comp->dev);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		wcd->rx_bias_count++;
		if (wcd->rx_bias_count == 1) {
			wcd9335_codec_init_flyback(comp);
			snd_soc_component_update_bits(comp,
						WCD9335_ANA_RX_SUPPLIES,
						WCD9335_ANA_RX_BIAS_ENABLE_MASK,
						WCD9335_ANA_RX_BIAS_ENABLE);
		}
		break;
	case SND_SOC_DAPM_POST_PMD:
		wcd->rx_bias_count--;
		if (!wcd->rx_bias_count)
			snd_soc_component_update_bits(comp,
					WCD9335_ANA_RX_SUPPLIES,
					WCD9335_ANA_RX_BIAS_ENABLE_MASK,
					WCD9335_ANA_RX_BIAS_DISABLE);
		break;
	};

	return 0;
}