#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wm1811_micdet_cb ;
typedef  scalar_t__ wm1811_mic_id_cb ;
typedef  int u16 ;
struct wm8994_priv {int mic_detecting; int jack_mic; int btn_mask; scalar_t__ jackdet; struct snd_soc_component* mic_id_cb_data; scalar_t__ mic_id_cb; void* micd_cb_data; scalar_t__ micd_cb; TYPE_1__* micdet; struct wm8994* wm8994; } ;
struct TYPE_4__ {int micd_lvl_sel; } ;
struct wm8994 {int type; TYPE_2__ pdata; } ;
struct snd_soc_jack {int dummy; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_3__ {struct snd_soc_jack* jack; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_JACK_BTN_0 ; 
 int SND_JACK_BTN_1 ; 
 int SND_JACK_BTN_2 ; 
 int SND_JACK_BTN_3 ; 
 int SND_JACK_BTN_4 ; 
 int SND_JACK_BTN_5 ; 
 scalar_t__ SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
#define  WM1811 129 
 int /*<<< orphan*/  WM1811_JACKDET_CTRL ; 
 int WM1811_JACKDET_DB ; 
 int /*<<< orphan*/  WM1811_JACKDET_MODE_JACK ; 
 int /*<<< orphan*/  WM1811_JACKDET_MODE_NONE ; 
#define  WM8958 128 
 int WM8958_MICB2_DISCH ; 
 int /*<<< orphan*/  WM8958_MICBIAS2 ; 
 int WM8958_MICD_ENA ; 
 int WM8958_MICD_LVL_SEL_MASK ; 
 int /*<<< orphan*/  WM8958_MIC_DETECT_1 ; 
 int /*<<< orphan*/  WM8958_MIC_DETECT_2 ; 
 int WM8994_LDO1_DISCH ; 
 int /*<<< orphan*/  WM8994_LDO_1 ; 
 scalar_t__ snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  wm1811_jackdet_set_mode (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 scalar_t__ wm8958_mic_id ; 
 int /*<<< orphan*/  wm8958_micd_set_rate (struct snd_soc_component*) ; 

int wm8958_mic_detect(struct snd_soc_component *component, struct snd_soc_jack *jack,
		      wm1811_micdet_cb det_cb, void *det_cb_data,
		      wm1811_mic_id_cb id_cb, void *id_cb_data)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	u16 micd_lvl_sel;

	switch (control->type) {
	case WM1811:
	case WM8958:
		break;
	default:
		return -EINVAL;
	}

	if (jack) {
		snd_soc_dapm_force_enable_pin(dapm, "CLK_SYS");
		snd_soc_dapm_sync(dapm);

		wm8994->micdet[0].jack = jack;

		if (det_cb) {
			wm8994->micd_cb = det_cb;
			wm8994->micd_cb_data = det_cb_data;
		} else {
			wm8994->mic_detecting = true;
			wm8994->jack_mic = false;
		}

		if (id_cb) {
			wm8994->mic_id_cb = id_cb;
			wm8994->mic_id_cb_data = id_cb_data;
		} else {
			wm8994->mic_id_cb = wm8958_mic_id;
			wm8994->mic_id_cb_data = component;
		}

		wm8958_micd_set_rate(component);

		/* Detect microphones and short circuits by default */
		if (control->pdata.micd_lvl_sel)
			micd_lvl_sel = control->pdata.micd_lvl_sel;
		else
			micd_lvl_sel = 0x41;

		wm8994->btn_mask = SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3 |
			SND_JACK_BTN_4 | SND_JACK_BTN_5;

		snd_soc_component_update_bits(component, WM8958_MIC_DETECT_2,
				    WM8958_MICD_LVL_SEL_MASK, micd_lvl_sel);

		WARN_ON(snd_soc_component_get_bias_level(component) > SND_SOC_BIAS_STANDBY);

		/*
		 * If we can use jack detection start off with that,
		 * otherwise jump straight to microphone detection.
		 */
		if (wm8994->jackdet) {
			/* Disable debounce for the initial detect */
			snd_soc_component_update_bits(component, WM1811_JACKDET_CTRL,
					    WM1811_JACKDET_DB, 0);

			snd_soc_component_update_bits(component, WM8958_MICBIAS2,
					    WM8958_MICB2_DISCH,
					    WM8958_MICB2_DISCH);
			snd_soc_component_update_bits(component, WM8994_LDO_1,
					    WM8994_LDO1_DISCH, 0);
			wm1811_jackdet_set_mode(component,
						WM1811_JACKDET_MODE_JACK);
		} else {
			snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1,
					    WM8958_MICD_ENA, WM8958_MICD_ENA);
		}

	} else {
		snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1,
				    WM8958_MICD_ENA, 0);
		wm1811_jackdet_set_mode(component, WM1811_JACKDET_MODE_NONE);
		snd_soc_dapm_disable_pin(dapm, "CLK_SYS");
		snd_soc_dapm_sync(dapm);
	}

	return 0;
}