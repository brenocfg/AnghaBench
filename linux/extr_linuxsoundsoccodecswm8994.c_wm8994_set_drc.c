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
struct wm8994_priv {int* drc_cfg; struct wm8994* wm8994; } ;
struct wm8994_pdata {TYPE_1__* drc_cfgs; } ;
struct wm8994 {struct wm8994_pdata pdata; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int* regs; } ;

/* Variables and functions */
 int WM8994_AIF1ADC1L_DRC_ENA ; 
 int WM8994_AIF1ADC1R_DRC_ENA ; 
 int WM8994_AIF1DAC1_DRC_ENA ; 
 int WM8994_DRC_REGS ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 
 int* wm8994_drc_base ; 

__attribute__((used)) static void wm8994_set_drc(struct snd_soc_component *component, int drc)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	struct wm8994_pdata *pdata = &control->pdata;
	int base = wm8994_drc_base[drc];
	int cfg = wm8994->drc_cfg[drc];
	int save, i;

	/* Save any enables; the configuration should clear them. */
	save = snd_soc_component_read32(component, base);
	save &= WM8994_AIF1DAC1_DRC_ENA | WM8994_AIF1ADC1L_DRC_ENA |
		WM8994_AIF1ADC1R_DRC_ENA;

	for (i = 0; i < WM8994_DRC_REGS; i++)
		snd_soc_component_update_bits(component, base + i, 0xffff,
				    pdata->drc_cfgs[cfg].regs[i]);

	snd_soc_component_update_bits(component, base, WM8994_AIF1DAC1_DRC_ENA |
			     WM8994_AIF1ADC1L_DRC_ENA |
			     WM8994_AIF1ADC1R_DRC_ENA, save);
}