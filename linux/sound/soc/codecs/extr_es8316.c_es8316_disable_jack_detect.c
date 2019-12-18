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
struct snd_soc_component {int dummy; } ;
struct es8316_priv {int /*<<< orphan*/  lock; TYPE_1__* jack; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES8316_GPIO_DEBOUNCE ; 
 int /*<<< orphan*/  ES8316_GPIO_ENABLE_INTERRUPT ; 
 int /*<<< orphan*/  SND_JACK_BTN_0 ; 
 int SND_JACK_MICROPHONE ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es8316_disable_micbias_for_mic_gnd_short_detect (struct snd_soc_component*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct es8316_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_report (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void es8316_disable_jack_detect(struct snd_soc_component *component)
{
	struct es8316_priv *es8316 = snd_soc_component_get_drvdata(component);

	disable_irq(es8316->irq);

	mutex_lock(&es8316->lock);

	snd_soc_component_update_bits(component, ES8316_GPIO_DEBOUNCE,
				      ES8316_GPIO_ENABLE_INTERRUPT, 0);

	if (es8316->jack->status & SND_JACK_MICROPHONE) {
		es8316_disable_micbias_for_mic_gnd_short_detect(component);
		snd_soc_jack_report(es8316->jack, 0, SND_JACK_BTN_0);
	}

	es8316->jack = NULL;

	mutex_unlock(&es8316->lock);
}