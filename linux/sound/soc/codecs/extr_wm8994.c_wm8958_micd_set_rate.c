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
struct wm8994_priv {int* aifclk; scalar_t__ jackdet; int /*<<< orphan*/  jack_mic; struct wm8994* wm8994; } ;
struct TYPE_2__ {int num_micd_rates; struct wm8958_micd_rate* micd_rates; } ;
struct wm8994 {TYPE_1__ pdata; } ;
struct wm8958_micd_rate {int idle; int start; int rate; scalar_t__ sysclk; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct wm8958_micd_rate*) ; 
 int WM8958_MICD_BIAS_STARTTIME_MASK ; 
 int WM8958_MICD_BIAS_STARTTIME_SHIFT ; 
 int WM8958_MICD_RATE_MASK ; 
 int WM8958_MICD_RATE_SHIFT ; 
 int /*<<< orphan*/  WM8958_MIC_DETECT_1 ; 
 int /*<<< orphan*/  WM8994_CLOCKING_1 ; 
 int WM8994_SYSCLK_SRC ; 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,char*) ; 
 struct wm8958_micd_rate* jackdet_rates ; 
 struct wm8958_micd_rate* micdet_rates ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void wm8958_micd_set_rate(struct snd_soc_component *component)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	int best, i, sysclk, val;
	bool idle;
	const struct wm8958_micd_rate *rates;
	int num_rates;

	idle = !wm8994->jack_mic;

	sysclk = snd_soc_component_read32(component, WM8994_CLOCKING_1);
	if (sysclk & WM8994_SYSCLK_SRC)
		sysclk = wm8994->aifclk[1];
	else
		sysclk = wm8994->aifclk[0];

	if (control->pdata.micd_rates) {
		rates = control->pdata.micd_rates;
		num_rates = control->pdata.num_micd_rates;
	} else if (wm8994->jackdet) {
		rates = jackdet_rates;
		num_rates = ARRAY_SIZE(jackdet_rates);
	} else {
		rates = micdet_rates;
		num_rates = ARRAY_SIZE(micdet_rates);
	}

	best = 0;
	for (i = 0; i < num_rates; i++) {
		if (rates[i].idle != idle)
			continue;
		if (abs(rates[i].sysclk - sysclk) <
		    abs(rates[best].sysclk - sysclk))
			best = i;
		else if (rates[best].idle != idle)
			best = i;
	}

	val = rates[best].start << WM8958_MICD_BIAS_STARTTIME_SHIFT
		| rates[best].rate << WM8958_MICD_RATE_SHIFT;

	dev_dbg(component->dev, "MICD rate %d,%d for %dHz %s\n",
		rates[best].start, rates[best].rate, sysclk,
		idle ? "idle" : "active");

	snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1,
			    WM8958_MICD_BIAS_STARTTIME_MASK |
			    WM8958_MICD_RATE_MASK, val);
}