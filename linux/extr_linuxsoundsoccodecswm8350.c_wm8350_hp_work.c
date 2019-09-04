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
typedef  int u16 ;
struct wm8350_jack_data {int report; int /*<<< orphan*/  jack; } ;
struct wm8350_data {struct wm8350* wm8350; } ;
struct wm8350 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_JACK_PIN_STATUS ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int,int) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8350_hp_work(struct wm8350_data *priv,
			   struct wm8350_jack_data *jack,
			   u16 mask)
{
	struct wm8350 *wm8350 = priv->wm8350;
	u16 reg;
	int report;

	reg = wm8350_reg_read(wm8350, WM8350_JACK_PIN_STATUS);
	if (reg & mask)
		report = jack->report;
	else
		report = 0;

	snd_soc_jack_report(jack->jack, report, jack->report);

}