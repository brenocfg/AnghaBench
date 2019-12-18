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
struct TYPE_2__ {struct snd_soc_component* component; } ;
struct wm8994_priv {int /*<<< orphan*/  mic_work; TYPE_1__ hubs; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 
 int /*<<< orphan*/  trace_snd_soc_jack_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t wm8994_mic_irq(int irq, void *data)
{
	struct wm8994_priv *priv = data;
	struct snd_soc_component *component = priv->hubs.component;

#ifndef CONFIG_SND_SOC_WM8994_MODULE
	trace_snd_soc_jack_irq(dev_name(component->dev));
#endif

	pm_wakeup_event(component->dev, 300);

	queue_delayed_work(system_power_efficient_wq,
			   &priv->mic_work, msecs_to_jiffies(250));

	return IRQ_HANDLED;
}