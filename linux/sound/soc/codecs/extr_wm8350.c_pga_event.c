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
struct wm8350_output {int active; int /*<<< orphan*/  ramp; } ;
struct wm8350_data {int /*<<< orphan*/  pga_work; struct wm8350_output out2; struct wm8350_output out1; } ;
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  WM8350_RAMP_DOWN ; 
 int /*<<< orphan*/  WM8350_RAMP_UP ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wm8350_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pga_event(struct snd_soc_dapm_widget *w,
		     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm8350_data *wm8350_data = snd_soc_component_get_drvdata(component);
	struct wm8350_output *out;

	switch (w->shift) {
	case 0:
	case 1:
		out = &wm8350_data->out1;
		break;
	case 2:
	case 3:
		out = &wm8350_data->out2;
		break;

	default:
		WARN(1, "Invalid shift %d\n", w->shift);
		return -1;
	}

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		out->ramp = WM8350_RAMP_UP;
		out->active = 1;

		schedule_delayed_work(&wm8350_data->pga_work,
				      msecs_to_jiffies(1));
		break;

	case SND_SOC_DAPM_PRE_PMD:
		out->ramp = WM8350_RAMP_DOWN;
		out->active = 0;

		schedule_delayed_work(&wm8350_data->pga_work,
				      msecs_to_jiffies(1));
		break;
	}

	return 0;
}