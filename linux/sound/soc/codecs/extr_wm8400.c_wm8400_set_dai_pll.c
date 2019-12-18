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
struct wm8400_priv {unsigned int fll_in; unsigned int fll_out; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct fll_factors {int fratio; int freq_ref; int k; int n; int outdiv; } ;
typedef  int /*<<< orphan*/  factors ;

/* Variables and functions */
 int /*<<< orphan*/  WM8400_FLL_CONTROL_1 ; 
 int /*<<< orphan*/  WM8400_FLL_CONTROL_2 ; 
 int /*<<< orphan*/  WM8400_FLL_CONTROL_3 ; 
 int /*<<< orphan*/  WM8400_FLL_CONTROL_4 ; 
 int WM8400_FLL_ENA ; 
 int WM8400_FLL_FRAC ; 
 int WM8400_FLL_FRATIO_MASK ; 
 int WM8400_FLL_OSC_ENA ; 
 int WM8400_FLL_OUTDIV_MASK ; 
 int WM8400_FLL_REF_FREQ ; 
 int WM8400_FLL_REF_FREQ_SHIFT ; 
 int /*<<< orphan*/  WM8400_POWER_MANAGEMENT_2 ; 
 int fll_factors (struct wm8400_priv*,struct fll_factors*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memset (struct fll_factors*,int /*<<< orphan*/ ,int) ; 
 struct wm8400_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8400_set_dai_pll(struct snd_soc_dai *codec_dai, int pll_id,
			      int source, unsigned int freq_in,
			      unsigned int freq_out)
{
	struct snd_soc_component *component = codec_dai->component;
	struct wm8400_priv *wm8400 = snd_soc_component_get_drvdata(component);
	struct fll_factors factors;
	int ret;
	u16 reg;

	if (freq_in == wm8400->fll_in && freq_out == wm8400->fll_out)
		return 0;

	if (freq_out) {
		ret = fll_factors(wm8400, &factors, freq_in, freq_out);
		if (ret != 0)
			return ret;
	} else {
		/* Bodge GCC 4.4.0 uninitialised variable warning - it
		 * doesn't seem capable of working out that we exit if
		 * freq_out is 0 before any of the uses. */
		memset(&factors, 0, sizeof(factors));
	}

	wm8400->fll_out = freq_out;
	wm8400->fll_in = freq_in;

	/* We *must* disable the FLL before any changes */
	reg = snd_soc_component_read32(component, WM8400_POWER_MANAGEMENT_2);
	reg &= ~WM8400_FLL_ENA;
	snd_soc_component_write(component, WM8400_POWER_MANAGEMENT_2, reg);

	reg = snd_soc_component_read32(component, WM8400_FLL_CONTROL_1);
	reg &= ~WM8400_FLL_OSC_ENA;
	snd_soc_component_write(component, WM8400_FLL_CONTROL_1, reg);

	if (!freq_out)
		return 0;

	reg &= ~(WM8400_FLL_REF_FREQ | WM8400_FLL_FRATIO_MASK);
	reg |= WM8400_FLL_FRAC | factors.fratio;
	reg |= factors.freq_ref << WM8400_FLL_REF_FREQ_SHIFT;
	snd_soc_component_write(component, WM8400_FLL_CONTROL_1, reg);

	snd_soc_component_write(component, WM8400_FLL_CONTROL_2, factors.k);
	snd_soc_component_write(component, WM8400_FLL_CONTROL_3, factors.n);

	reg = snd_soc_component_read32(component, WM8400_FLL_CONTROL_4);
	reg &= ~WM8400_FLL_OUTDIV_MASK;
	reg |= factors.outdiv;
	snd_soc_component_write(component, WM8400_FLL_CONTROL_4, reg);

	return 0;
}