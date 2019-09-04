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
struct wm8994_priv {int /*<<< orphan*/  btn_mask; TYPE_1__* micdet; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  jack; } ;

/* Variables and functions */
 int SND_JACK_BTN_0 ; 
 int SND_JACK_BTN_1 ; 
 int SND_JACK_BTN_2 ; 
 int SND_JACK_BTN_3 ; 
 int SND_JACK_BTN_4 ; 
 int SND_JACK_BTN_5 ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8958_button_det(struct snd_soc_component *component, u16 status)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	int report;

	report = 0;
	if (status & 0x4)
		report |= SND_JACK_BTN_0;

	if (status & 0x8)
		report |= SND_JACK_BTN_1;

	if (status & 0x10)
		report |= SND_JACK_BTN_2;

	if (status & 0x20)
		report |= SND_JACK_BTN_3;

	if (status & 0x40)
		report |= SND_JACK_BTN_4;

	if (status & 0x80)
		report |= SND_JACK_BTN_5;

	snd_soc_jack_report(wm8994->micdet[0].jack, report,
			    wm8994->btn_mask);
}