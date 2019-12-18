#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wm8994_priv {int mic_detecting; int jack_mic; TYPE_1__* micdet; int /*<<< orphan*/  open_circuit_work; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
 int WM8958_MICD_STS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 
 int /*<<< orphan*/  wm1811_micd_stop (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8958_micd_set_rate (struct snd_soc_component*) ; 

__attribute__((used)) static void wm8958_mic_id(void *data, u16 status)
{
	struct snd_soc_component *component = data;
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	/* Either nothing present or just starting detection */
	if (!(status & WM8958_MICD_STS)) {
		/* If nothing present then clear our statuses */
		dev_dbg(component->dev, "Detected open circuit\n");

		queue_delayed_work(system_power_efficient_wq,
				   &wm8994->open_circuit_work,
				   msecs_to_jiffies(2500));
		return;
	}

	/* If the measurement is showing a high impedence we've got a
	 * microphone.
	 */
	if (status & 0x600) {
		dev_dbg(component->dev, "Detected microphone\n");

		wm8994->mic_detecting = false;
		wm8994->jack_mic = true;

		wm8958_micd_set_rate(component);

		snd_soc_jack_report(wm8994->micdet[0].jack, SND_JACK_HEADSET,
				    SND_JACK_HEADSET);
	}


	if (status & 0xfc) {
		dev_dbg(component->dev, "Detected headphone\n");
		wm8994->mic_detecting = false;

		wm8958_micd_set_rate(component);

		/* If we have jackdet that will detect removal */
		wm1811_micd_stop(component);

		snd_soc_jack_report(wm8994->micdet[0].jack, SND_JACK_HEADPHONE,
				    SND_JACK_HEADSET);
	}
}