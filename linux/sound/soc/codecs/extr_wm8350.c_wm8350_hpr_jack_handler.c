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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct wm8350_data {TYPE_1__ hpr; struct wm8350* wm8350; } ;
struct wm8350 {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 
 int /*<<< orphan*/  trace_snd_soc_jack_irq (char*) ; 

__attribute__((used)) static irqreturn_t wm8350_hpr_jack_handler(int irq, void *data)
{
	struct wm8350_data *priv = data;
	struct wm8350 *wm8350 = priv->wm8350;

#ifndef CONFIG_SND_SOC_WM8350_MODULE
	trace_snd_soc_jack_irq("WM8350 HPR");
#endif

	if (device_may_wakeup(wm8350->dev))
		pm_wakeup_event(wm8350->dev, 250);

	queue_delayed_work(system_power_efficient_wq,
			   &priv->hpr.work, msecs_to_jiffies(200));

	return IRQ_HANDLED;
}