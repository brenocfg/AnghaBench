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
struct wm8994_priv {int clk_has_run; int /*<<< orphan*/  jackdet_bootstrap; int /*<<< orphan*/  jackdet; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 130 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int configure_clock (struct snd_soc_component*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int clk_sys_event(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		return configure_clock(component);

	case SND_SOC_DAPM_POST_PMU:
		/*
		 * JACKDET won't run until we start the clock and it
		 * only reports deltas, make sure we notify the state
		 * up the stack on startup.  Use a *very* generous
		 * timeout for paranoia, there's no urgency and we
		 * don't want false reports.
		 */
		if (wm8994->jackdet && !wm8994->clk_has_run) {
			queue_delayed_work(system_power_efficient_wq,
					   &wm8994->jackdet_bootstrap,
					   msecs_to_jiffies(1000));
			wm8994->clk_has_run = true;
		}
		break;

	case SND_SOC_DAPM_POST_PMD:
		configure_clock(component);
		break;
	}

	return 0;
}