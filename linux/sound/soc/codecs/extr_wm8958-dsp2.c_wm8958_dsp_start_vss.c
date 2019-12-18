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
struct wm8994_priv {size_t mbc_cfg; size_t vss_cfg; size_t vss_hpf_cfg; scalar_t__* vss_ena; scalar_t__* hpf1_ena; scalar_t__* hpf2_ena; scalar_t__* mbc_ena; scalar_t__ mbc_vss; struct wm8994* wm8994; } ;
struct TYPE_2__ {struct wm8958_vss_hpf_cfg* vss_hpf_cfgs; scalar_t__ num_vss_hpf_cfgs; struct wm8958_vss_cfg* vss_cfgs; scalar_t__ num_vss_cfgs; struct wm8958_mbc_cfg* mbc_cfgs; scalar_t__ num_mbc_cfgs; } ;
struct wm8994 {TYPE_1__ pdata; } ;
struct wm8958_vss_hpf_cfg {int* regs; } ;
struct wm8958_vss_cfg {int* regs; } ;
struct wm8958_mbc_cfg {int* combined_regs; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  WM8958_DSP2_CONFIG ; 
 int WM8958_DSP2_ENA ; 
 int WM8958_DSP2_EXECCONTROL ; 
 int /*<<< orphan*/  WM8958_DSP2_PROGRAM ; 
 int WM8958_DSP2_RUNR ; 
 int WM8958_MBC_ENA ; 
 int WM8958_MBC_SEL_MASK ; 
 int WM8958_MBC_SEL_SHIFT ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int,int) ; 
 int /*<<< orphan*/  wm8958_dsp2_fw (struct snd_soc_component*,char*,scalar_t__,int) ; 

__attribute__((used)) static void wm8958_dsp_start_vss(struct snd_soc_component *component, int path)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	int i, ena;

	if (wm8994->mbc_vss)
		wm8958_dsp2_fw(component, "MBC+VSS", wm8994->mbc_vss, false);

	snd_soc_component_update_bits(component, WM8958_DSP2_PROGRAM,
			    WM8958_DSP2_ENA, WM8958_DSP2_ENA);

	/* If we've got user supplied settings use them */
	if (control->pdata.num_mbc_cfgs) {
		struct wm8958_mbc_cfg *cfg
			= &control->pdata.mbc_cfgs[wm8994->mbc_cfg];

		for (i = 0; i < ARRAY_SIZE(cfg->combined_regs); i++)
			snd_soc_component_write(component, i + 0x2800,
				      cfg->combined_regs[i]);
	}

	if (control->pdata.num_vss_cfgs) {
		struct wm8958_vss_cfg *cfg
			= &control->pdata.vss_cfgs[wm8994->vss_cfg];

		for (i = 0; i < ARRAY_SIZE(cfg->regs); i++)
			snd_soc_component_write(component, i + 0x2600, cfg->regs[i]);
	}

	if (control->pdata.num_vss_hpf_cfgs) {
		struct wm8958_vss_hpf_cfg *cfg
			= &control->pdata.vss_hpf_cfgs[wm8994->vss_hpf_cfg];

		for (i = 0; i < ARRAY_SIZE(cfg->regs); i++)
			snd_soc_component_write(component, i + 0x2400, cfg->regs[i]);
	}

	/* Run the DSP */
	snd_soc_component_write(component, WM8958_DSP2_EXECCONTROL,
		      WM8958_DSP2_RUNR);

	/* Enable the algorithms we've selected */
	ena = 0;
	if (wm8994->mbc_ena[path])
		ena |= 0x8;
	if (wm8994->hpf2_ena[path])
		ena |= 0x4;
	if (wm8994->hpf1_ena[path])
		ena |= 0x2;
	if (wm8994->vss_ena[path])
		ena |= 0x1;

	snd_soc_component_write(component, 0x2201, ena);

	/* Switch the DSP into the data path */
	snd_soc_component_update_bits(component, WM8958_DSP2_CONFIG,
			    WM8958_MBC_SEL_MASK | WM8958_MBC_ENA,
			    path << WM8958_MBC_SEL_SHIFT | WM8958_MBC_ENA);
}