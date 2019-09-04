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
struct wm8900_priv {unsigned int fll_in; unsigned int fll_out; } ;
struct snd_soc_component {int dummy; } ;
struct _fll_div {int fll_ratio; int n; int fllclk_div; int k; scalar_t__ fll_slow_lock_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8900_REG_CLOCKING1 ; 
 int WM8900_REG_CLOCKING1_MCLK_SRC ; 
 int /*<<< orphan*/  WM8900_REG_FLLCTL1 ; 
 int WM8900_REG_FLLCTL1_OSC_ENA ; 
 int /*<<< orphan*/  WM8900_REG_FLLCTL2 ; 
 int /*<<< orphan*/  WM8900_REG_FLLCTL3 ; 
 int /*<<< orphan*/  WM8900_REG_FLLCTL4 ; 
 int /*<<< orphan*/  WM8900_REG_FLLCTL5 ; 
 int /*<<< orphan*/  WM8900_REG_FLLCTL6 ; 
 int WM8900_REG_FLLCTL6_FLL_SLOW_LOCK_REF ; 
 int /*<<< orphan*/  WM8900_REG_POWER1 ; 
 int WM8900_REG_POWER1_FLL_ENA ; 
 scalar_t__ fll_factors (struct _fll_div*,unsigned int,unsigned int) ; 
 struct wm8900_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8900_set_fll(struct snd_soc_component *component,
	int fll_id, unsigned int freq_in, unsigned int freq_out)
{
	struct wm8900_priv *wm8900 = snd_soc_component_get_drvdata(component);
	struct _fll_div fll_div;

	if (wm8900->fll_in == freq_in && wm8900->fll_out == freq_out)
		return 0;

	/* The digital side should be disabled during any change. */
	snd_soc_component_update_bits(component, WM8900_REG_POWER1,
			    WM8900_REG_POWER1_FLL_ENA, 0);

	/* Disable the FLL? */
	if (!freq_in || !freq_out) {
		snd_soc_component_update_bits(component, WM8900_REG_CLOCKING1,
				    WM8900_REG_CLOCKING1_MCLK_SRC, 0);
		snd_soc_component_update_bits(component, WM8900_REG_FLLCTL1,
				    WM8900_REG_FLLCTL1_OSC_ENA, 0);
		wm8900->fll_in = freq_in;
		wm8900->fll_out = freq_out;

		return 0;
	}

	if (fll_factors(&fll_div, freq_in, freq_out) != 0)
		goto reenable;

	wm8900->fll_in = freq_in;
	wm8900->fll_out = freq_out;

	/* The osclilator *MUST* be enabled before we enable the
	 * digital circuit. */
	snd_soc_component_write(component, WM8900_REG_FLLCTL1,
		     fll_div.fll_ratio | WM8900_REG_FLLCTL1_OSC_ENA);

	snd_soc_component_write(component, WM8900_REG_FLLCTL4, fll_div.n >> 5);
	snd_soc_component_write(component, WM8900_REG_FLLCTL5,
		     (fll_div.fllclk_div << 6) | (fll_div.n & 0x1f));

	if (fll_div.k) {
		snd_soc_component_write(component, WM8900_REG_FLLCTL2,
			     (fll_div.k >> 8) | 0x100);
		snd_soc_component_write(component, WM8900_REG_FLLCTL3, fll_div.k & 0xff);
	} else
		snd_soc_component_write(component, WM8900_REG_FLLCTL2, 0);

	if (fll_div.fll_slow_lock_ref)
		snd_soc_component_write(component, WM8900_REG_FLLCTL6,
			     WM8900_REG_FLLCTL6_FLL_SLOW_LOCK_REF);
	else
		snd_soc_component_write(component, WM8900_REG_FLLCTL6, 0);

	snd_soc_component_update_bits(component, WM8900_REG_POWER1,
			    WM8900_REG_POWER1_FLL_ENA,
			    WM8900_REG_POWER1_FLL_ENA);

reenable:
	snd_soc_component_update_bits(component, WM8900_REG_CLOCKING1,
			    WM8900_REG_CLOCKING1_MCLK_SRC,
			    WM8900_REG_CLOCKING1_MCLK_SRC);
	return 0;
}