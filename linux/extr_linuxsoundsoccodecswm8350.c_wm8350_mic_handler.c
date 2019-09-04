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
struct TYPE_2__ {int short_report; int report; int /*<<< orphan*/  jack; } ;
struct wm8350_data {TYPE_1__ mic; struct wm8350* wm8350; } ;
struct wm8350 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int WM8350_JACK_MICSCD_LVL ; 
 int WM8350_JACK_MICSD_LVL ; 
 int /*<<< orphan*/  WM8350_JACK_PIN_STATUS ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  trace_snd_soc_jack_irq (char*) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t wm8350_mic_handler(int irq, void *data)
{
	struct wm8350_data *priv = data;
	struct wm8350 *wm8350 = priv->wm8350;
	u16 reg;
	int report = 0;

#ifndef CONFIG_SND_SOC_WM8350_MODULE
	trace_snd_soc_jack_irq("WM8350 mic");
#endif

	reg = wm8350_reg_read(wm8350, WM8350_JACK_PIN_STATUS);
	if (reg & WM8350_JACK_MICSCD_LVL)
		report |= priv->mic.short_report;
	if (reg & WM8350_JACK_MICSD_LVL)
		report |= priv->mic.report;

	snd_soc_jack_report(priv->mic.jack, report,
			    priv->mic.report | priv->mic.short_report);

	return IRQ_HANDLED;
}