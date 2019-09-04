#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct snd_soc_component* component; } ;
struct wm8994_priv {int mic_detecting; int jack_mic; int btn_mask; TYPE_3__* micdet; int /*<<< orphan*/  accdet_lock; int /*<<< orphan*/  mic_work; int /*<<< orphan*/  mic_complete_work; TYPE_1__ hubs; struct wm8994* wm8994; } ;
struct TYPE_5__ {int micdet_delay; scalar_t__ jd_ext_cap; } ;
struct wm8994 {TYPE_2__ pdata; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_MECHANICAL ; 
 int /*<<< orphan*/  WM1811_JACKDET_CTRL ; 
 int /*<<< orphan*/  WM1811_JACKDET_DB ; 
 int WM1811_JACKDET_LVL ; 
 int /*<<< orphan*/  WM1811_JACKDET_MODE_JACK ; 
 int /*<<< orphan*/  WM8958_MICB2_DISCH ; 
 int /*<<< orphan*/  WM8958_MICBIAS2 ; 
 int /*<<< orphan*/  WM8958_MICD_ENA ; 
 int /*<<< orphan*/  WM8958_MIC_DETECT_1 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 
 int /*<<< orphan*/  wm1811_jackdet_set_mode (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8958_micd_set_rate (struct snd_soc_component*) ; 

__attribute__((used)) static irqreturn_t wm1811_jackdet_irq(int irq, void *data)
{
	struct wm8994_priv *wm8994 = data;
	struct wm8994 *control = wm8994->wm8994;
	struct snd_soc_component *component = wm8994->hubs.component;
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int reg, delay;
	bool present;

	pm_runtime_get_sync(component->dev);

	cancel_delayed_work_sync(&wm8994->mic_complete_work);

	mutex_lock(&wm8994->accdet_lock);

	reg = snd_soc_component_read32(component, WM1811_JACKDET_CTRL);
	if (reg < 0) {
		dev_err(component->dev, "Failed to read jack status: %d\n", reg);
		mutex_unlock(&wm8994->accdet_lock);
		pm_runtime_put(component->dev);
		return IRQ_NONE;
	}

	dev_dbg(component->dev, "JACKDET %x\n", reg);

	present = reg & WM1811_JACKDET_LVL;

	if (present) {
		dev_dbg(component->dev, "Jack detected\n");

		wm8958_micd_set_rate(component);

		snd_soc_component_update_bits(component, WM8958_MICBIAS2,
				    WM8958_MICB2_DISCH, 0);

		/* Disable debounce while inserted */
		snd_soc_component_update_bits(component, WM1811_JACKDET_CTRL,
				    WM1811_JACKDET_DB, 0);

		delay = control->pdata.micdet_delay;
		queue_delayed_work(system_power_efficient_wq,
				   &wm8994->mic_work,
				   msecs_to_jiffies(delay));
	} else {
		dev_dbg(component->dev, "Jack not detected\n");

		cancel_delayed_work_sync(&wm8994->mic_work);

		snd_soc_component_update_bits(component, WM8958_MICBIAS2,
				    WM8958_MICB2_DISCH, WM8958_MICB2_DISCH);

		/* Enable debounce while removed */
		snd_soc_component_update_bits(component, WM1811_JACKDET_CTRL,
				    WM1811_JACKDET_DB, WM1811_JACKDET_DB);

		wm8994->mic_detecting = false;
		wm8994->jack_mic = false;
		snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1,
				    WM8958_MICD_ENA, 0);
		wm1811_jackdet_set_mode(component, WM1811_JACKDET_MODE_JACK);
	}

	mutex_unlock(&wm8994->accdet_lock);

	/* Turn off MICBIAS if it was on for an external cap */
	if (control->pdata.jd_ext_cap && !present)
		snd_soc_dapm_disable_pin(dapm, "MICBIAS2");

	if (present)
		snd_soc_jack_report(wm8994->micdet[0].jack,
				    SND_JACK_MECHANICAL, SND_JACK_MECHANICAL);
	else
		snd_soc_jack_report(wm8994->micdet[0].jack, 0,
				    SND_JACK_MECHANICAL | SND_JACK_HEADSET |
				    wm8994->btn_mask);

	/* Since we only report deltas force an update, ensures we
	 * avoid bootstrapping issues with the core. */
	snd_soc_jack_report(wm8994->micdet[0].jack, 0, 0);

	pm_runtime_put(component->dev);
	return IRQ_HANDLED;
}