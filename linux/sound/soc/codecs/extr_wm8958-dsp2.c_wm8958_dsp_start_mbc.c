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
struct wm8994_priv {size_t mbc_cfg; scalar_t__ mbc; struct wm8994* wm8994; } ;
struct TYPE_2__ {struct wm8958_mbc_cfg* mbc_cfgs; scalar_t__ num_mbc_cfgs; } ;
struct wm8994 {TYPE_1__ pdata; } ;
struct wm8958_mbc_cfg {int /*<<< orphan*/ * cutoff_regs; int /*<<< orphan*/ * coeff_regs; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM8958_DSP2_CONFIG ; 
 int WM8958_DSP2_ENA ; 
 scalar_t__ WM8958_DSP2_EXECCONTROL ; 
 int /*<<< orphan*/  WM8958_DSP2_PROGRAM ; 
 int /*<<< orphan*/  WM8958_DSP2_RUNR ; 
 scalar_t__ WM8958_MBC_BAND_1_K_1 ; 
 scalar_t__ WM8958_MBC_BAND_2_LOWER_CUTOFF_C1_1 ; 
 int WM8958_MBC_ENA ; 
 int WM8958_MBC_SEL_MASK ; 
 int WM8958_MBC_SEL_SHIFT ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8958_dsp2_fw (struct snd_soc_component*,char*,scalar_t__,int) ; 

__attribute__((used)) static void wm8958_dsp_start_mbc(struct snd_soc_component *component, int path)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	int i;

	/* If the DSP is already running then noop */
	if (snd_soc_component_read32(component, WM8958_DSP2_PROGRAM) & WM8958_DSP2_ENA)
		return;

	/* If we have MBC firmware download it */
	if (wm8994->mbc)
		wm8958_dsp2_fw(component, "MBC", wm8994->mbc, false);

	snd_soc_component_update_bits(component, WM8958_DSP2_PROGRAM,
			    WM8958_DSP2_ENA, WM8958_DSP2_ENA);

	/* If we've got user supplied MBC settings use them */
	if (control->pdata.num_mbc_cfgs) {
		struct wm8958_mbc_cfg *cfg
			= &control->pdata.mbc_cfgs[wm8994->mbc_cfg];

		for (i = 0; i < ARRAY_SIZE(cfg->coeff_regs); i++)
			snd_soc_component_write(component, i + WM8958_MBC_BAND_1_K_1,
				      cfg->coeff_regs[i]);

		for (i = 0; i < ARRAY_SIZE(cfg->cutoff_regs); i++)
			snd_soc_component_write(component,
				      i + WM8958_MBC_BAND_2_LOWER_CUTOFF_C1_1,
				      cfg->cutoff_regs[i]);
	}

	/* Run the DSP */
	snd_soc_component_write(component, WM8958_DSP2_EXECCONTROL,
		      WM8958_DSP2_RUNR);

	/* And we're off! */
	snd_soc_component_update_bits(component, WM8958_DSP2_CONFIG,
			    WM8958_MBC_ENA |
			    WM8958_MBC_SEL_MASK,
			    path << WM8958_MBC_SEL_SHIFT |
			    WM8958_MBC_ENA);
}