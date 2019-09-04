#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wm8994_priv {TYPE_2__* wm8994; int /*<<< orphan*/  jackdet; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_3__ {scalar_t__ jd_ext_cap; } ;
struct TYPE_4__ {TYPE_1__ pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM1811_JACKDET_MODE_JACK ; 
 int /*<<< orphan*/  WM8958_MICD_ENA ; 
 int /*<<< orphan*/  WM8958_MIC_DETECT_1 ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  wm1811_jackdet_set_mode (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm1811_micd_stop(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	if (!wm8994->jackdet)
		return;

	snd_soc_component_update_bits(component, WM8958_MIC_DETECT_1, WM8958_MICD_ENA, 0);

	wm1811_jackdet_set_mode(component, WM1811_JACKDET_MODE_JACK);

	if (wm8994->wm8994->pdata.jd_ext_cap)
		snd_soc_dapm_disable_pin(dapm, "MICBIAS2");
}