#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct snd_soc_component* component; } ;
struct wm8994_priv {int btn_mask; int mic_detecting; int mic_status; int /*<<< orphan*/  mic_complete_work; TYPE_4__* wm8994; TYPE_2__* micdet; scalar_t__ jackdet; int /*<<< orphan*/  open_circuit_work; TYPE_1__ hubs; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int mic_id_delay; } ;
struct TYPE_8__ {TYPE_3__ pdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SND_JACK_HEADSET ; 
 int SND_JACK_MECHANICAL ; 
 int /*<<< orphan*/  WM1811_JACKDET_CTRL ; 
 int WM1811_JACKDET_LVL ; 
 int WM8958_MICD_ENA ; 
 int WM8958_MICD_LVL_MASK ; 
 int WM8958_MICD_STS ; 
 int WM8958_MICD_VALID ; 
 int /*<<< orphan*/  WM8958_MIC_DETECT_1 ; 
 int /*<<< orphan*/  WM8958_MIC_DETECT_3 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 
 int /*<<< orphan*/  trace_snd_soc_jack_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8958_button_det (struct snd_soc_component*,int) ; 

__attribute__((used)) static irqreturn_t wm8958_mic_irq(int irq, void *data)
{
	struct wm8994_priv *wm8994 = data;
	struct snd_soc_component *component = wm8994->hubs.component;
	int reg, count, ret, id_delay;

	/*
	 * Jack detection may have detected a removal simulataneously
	 * with an update of the MICDET status; if so it will have
	 * stopped detection and we can ignore this interrupt.
	 */
	if (!(snd_soc_component_read32(component, WM8958_MIC_DETECT_1) & WM8958_MICD_ENA))
		return IRQ_HANDLED;

	cancel_delayed_work_sync(&wm8994->mic_complete_work);
	cancel_delayed_work_sync(&wm8994->open_circuit_work);

	pm_runtime_get_sync(component->dev);

	/* We may occasionally read a detection without an impedence
	 * range being provided - if that happens loop again.
	 */
	count = 10;
	do {
		reg = snd_soc_component_read32(component, WM8958_MIC_DETECT_3);
		if (reg < 0) {
			dev_err(component->dev,
				"Failed to read mic detect status: %d\n",
				reg);
			pm_runtime_put(component->dev);
			return IRQ_NONE;
		}

		if (!(reg & WM8958_MICD_VALID)) {
			dev_dbg(component->dev, "Mic detect data not valid\n");
			goto out;
		}

		if (!(reg & WM8958_MICD_STS) || (reg & WM8958_MICD_LVL_MASK))
			break;

		msleep(1);
	} while (count--);

	if (count == 0)
		dev_warn(component->dev, "No impedance range reported for jack\n");

#ifndef CONFIG_SND_SOC_WM8994_MODULE
	trace_snd_soc_jack_irq(dev_name(component->dev));
#endif

	/* Avoid a transient report when the accessory is being removed */
	if (wm8994->jackdet) {
		ret = snd_soc_component_read32(component, WM1811_JACKDET_CTRL);
		if (ret < 0) {
			dev_err(component->dev, "Failed to read jack status: %d\n",
				ret);
		} else if (!(ret & WM1811_JACKDET_LVL)) {
			dev_dbg(component->dev, "Ignoring removed jack\n");
			goto out;
		}
	} else if (!(reg & WM8958_MICD_STS)) {
		snd_soc_jack_report(wm8994->micdet[0].jack, 0,
				    SND_JACK_MECHANICAL | SND_JACK_HEADSET |
				    wm8994->btn_mask);
		wm8994->mic_detecting = true;
		goto out;
	}

	wm8994->mic_status = reg;
	id_delay = wm8994->wm8994->pdata.mic_id_delay;

	if (wm8994->mic_detecting)
		queue_delayed_work(system_power_efficient_wq,
				   &wm8994->mic_complete_work,
				   msecs_to_jiffies(id_delay));
	else
		wm8958_button_det(component, reg);

out:
	pm_runtime_put(component->dev);
	return IRQ_HANDLED;
}