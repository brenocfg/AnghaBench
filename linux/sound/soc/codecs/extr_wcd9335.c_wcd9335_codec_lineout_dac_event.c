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
struct wcd9335_codec {int /*<<< orphan*/  clsh_ctrl; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLS_AB ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  WCD_CLSH_EVENT_POST_PA ; 
 int /*<<< orphan*/  WCD_CLSH_EVENT_PRE_DAC ; 
 int /*<<< orphan*/  WCD_CLSH_STATE_LO ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcd_clsh_ctrl_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcd9335_codec_lineout_dac_event(struct snd_soc_dapm_widget *w,
					   struct snd_kcontrol *kc, int event)
{
	struct snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	struct wcd9335_codec *wcd = dev_get_drvdata(comp->dev);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_PRE_DAC,
					WCD_CLSH_STATE_LO, CLS_AB);
		break;
	case SND_SOC_DAPM_POST_PMD:
		wcd_clsh_ctrl_set_state(wcd->clsh_ctrl, WCD_CLSH_EVENT_POST_PA,
					WCD_CLSH_STATE_LO, CLS_AB);
		break;
	}

	return 0;
}