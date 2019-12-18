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
struct wm5100_priv {int jack_detecting; struct snd_soc_jack* jack; scalar_t__ jack_flips; } ;
struct snd_soc_jack {int dummy; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int WM5100_ACCDET_BIAS_STARTTIME_MASK ; 
 int WM5100_ACCDET_BIAS_STARTTIME_SHIFT ; 
 int WM5100_ACCDET_ENA ; 
 int WM5100_ACCDET_RATE_MASK ; 
 int WM5100_IM_ACCDET_EINT ; 
 int WM5100_IM_HPDET_EINT ; 
 int /*<<< orphan*/  WM5100_INTERRUPT_STATUS_3_MASK ; 
 int /*<<< orphan*/  WM5100_MIC_DETECT_1 ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm5100_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync_unlocked (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  wm5100_set_detect_mode (struct wm5100_priv*,int /*<<< orphan*/ ) ; 

int wm5100_detect(struct snd_soc_component *component, struct snd_soc_jack *jack)
{
	struct wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	if (jack) {
		wm5100->jack = jack;
		wm5100->jack_detecting = true;
		wm5100->jack_flips = 0;

		wm5100_set_detect_mode(wm5100, 0);

		/* Slowest detection rate, gives debounce for initial
		 * detection */
		snd_soc_component_update_bits(component, WM5100_MIC_DETECT_1,
				    WM5100_ACCDET_BIAS_STARTTIME_MASK |
				    WM5100_ACCDET_RATE_MASK,
				    (7 << WM5100_ACCDET_BIAS_STARTTIME_SHIFT) |
				    WM5100_ACCDET_RATE_MASK);

		/* We need the charge pump to power MICBIAS */
		snd_soc_dapm_mutex_lock(dapm);

		snd_soc_dapm_force_enable_pin_unlocked(dapm, "CP2");
		snd_soc_dapm_force_enable_pin_unlocked(dapm, "SYSCLK");

		snd_soc_dapm_sync_unlocked(dapm);

		snd_soc_dapm_mutex_unlock(dapm);

		/* We start off just enabling microphone detection - even a
		 * plain headphone will trigger detection.
		 */
		snd_soc_component_update_bits(component, WM5100_MIC_DETECT_1,
				    WM5100_ACCDET_ENA, WM5100_ACCDET_ENA);

		snd_soc_component_update_bits(component, WM5100_INTERRUPT_STATUS_3_MASK,
				    WM5100_IM_ACCDET_EINT, 0);
	} else {
		snd_soc_component_update_bits(component, WM5100_INTERRUPT_STATUS_3_MASK,
				    WM5100_IM_HPDET_EINT |
				    WM5100_IM_ACCDET_EINT,
				    WM5100_IM_HPDET_EINT |
				    WM5100_IM_ACCDET_EINT);
		snd_soc_component_update_bits(component, WM5100_MIC_DETECT_1,
				    WM5100_ACCDET_ENA, 0);
		wm5100->jack = NULL;
	}

	return 0;
}