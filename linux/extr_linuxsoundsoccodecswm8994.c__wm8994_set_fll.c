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
struct wm8994_priv {int* aifdiv; int /*<<< orphan*/ * aifclk; TYPE_1__* fll; int /*<<< orphan*/ * fll_locked; scalar_t__ fll_locked_irq; scalar_t__ fll_byp; struct wm8994* wm8994; } ;
struct wm8994 {int type; int revision; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct fll_div {int outdiv; int fll_fratio; int k; int n; int lambda; int clk_ref_div; } ;
struct TYPE_2__ {int src; unsigned int in; unsigned int out; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  WM8958 136 
 int WM8958_FLL1_BYP ; 
 int WM8958_FLL1_EFS_1 ; 
 int WM8958_FLL1_EFS_2 ; 
 int WM8958_FLL1_EFS_ENA ; 
 int WM8958_FLL1_LAMBDA_MASK ; 
#define  WM8994 135 
 int WM8994_AIF1CLK_ENA ; 
 int WM8994_AIF1CLK_RATE_MASK ; 
 int WM8994_AIF1CLK_SRC_MASK ; 
 int WM8994_AIF1_CLOCKING_1 ; 
 int WM8994_AIF1_RATE ; 
 int WM8994_AIF2CLK_RATE_MASK ; 
 int WM8994_AIF2_CLOCKING_1 ; 
 int WM8994_AIF2_RATE ; 
 int WM8994_CLOCKING_1 ; 
#define  WM8994_FLL1 134 
 int WM8994_FLL1_CONTROL_1 ; 
 int WM8994_FLL1_CONTROL_2 ; 
 int WM8994_FLL1_CONTROL_3 ; 
 int WM8994_FLL1_CONTROL_4 ; 
 int WM8994_FLL1_CONTROL_5 ; 
 int WM8994_FLL1_ENA ; 
 int WM8994_FLL1_FRAC ; 
 int WM8994_FLL1_FRATIO_MASK ; 
 int WM8994_FLL1_FRATIO_SHIFT ; 
 int WM8994_FLL1_FRC_NCO ; 
 int WM8994_FLL1_FRC_NCO_SHIFT ; 
 int WM8994_FLL1_K_MASK ; 
 int WM8994_FLL1_N_MASK ; 
 int WM8994_FLL1_N_SHIFT ; 
 int WM8994_FLL1_OSC_ENA ; 
 int WM8994_FLL1_OUTDIV_MASK ; 
 int WM8994_FLL1_OUTDIV_SHIFT ; 
 int WM8994_FLL1_REFCLK_DIV_MASK ; 
 int WM8994_FLL1_REFCLK_DIV_SHIFT ; 
 int WM8994_FLL1_REFCLK_SRC_MASK ; 
#define  WM8994_FLL2 133 
#define  WM8994_FLL_SRC_BCLK 132 
#define  WM8994_FLL_SRC_INTERNAL 131 
#define  WM8994_FLL_SRC_LRCLK 130 
#define  WM8994_FLL_SRC_MCLK1 129 
#define  WM8994_FLL_SRC_MCLK2 128 
 int WM8994_SYSCLK_SRC ; 
 int /*<<< orphan*/  active_dereference (struct snd_soc_component*) ; 
 int /*<<< orphan*/  active_reference (struct snd_soc_component*) ; 
 int /*<<< orphan*/  configure_clock (struct snd_soc_component*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 
 int /*<<< orphan*/  try_wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmid_dereference (struct snd_soc_component*) ; 
 int /*<<< orphan*/  vmid_reference (struct snd_soc_component*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wm8994_get_fll_config (struct wm8994*,struct fll_div*,unsigned int,unsigned int) ; 

__attribute__((used)) static int _wm8994_set_fll(struct snd_soc_component *component, int id, int src,
			  unsigned int freq_in, unsigned int freq_out)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;
	int reg_offset, ret;
	struct fll_div fll;
	u16 reg, clk1, aif_reg, aif_src;
	unsigned long timeout;
	bool was_enabled;

	switch (id) {
	case WM8994_FLL1:
		reg_offset = 0;
		id = 0;
		aif_src = 0x10;
		break;
	case WM8994_FLL2:
		reg_offset = 0x20;
		id = 1;
		aif_src = 0x18;
		break;
	default:
		return -EINVAL;
	}

	reg = snd_soc_component_read32(component, WM8994_FLL1_CONTROL_1 + reg_offset);
	was_enabled = reg & WM8994_FLL1_ENA;

	switch (src) {
	case 0:
		/* Allow no source specification when stopping */
		if (freq_out)
			return -EINVAL;
		src = wm8994->fll[id].src;
		break;
	case WM8994_FLL_SRC_MCLK1:
	case WM8994_FLL_SRC_MCLK2:
	case WM8994_FLL_SRC_LRCLK:
	case WM8994_FLL_SRC_BCLK:
		break;
	case WM8994_FLL_SRC_INTERNAL:
		freq_in = 12000000;
		freq_out = 12000000;
		break;
	default:
		return -EINVAL;
	}

	/* Are we changing anything? */
	if (wm8994->fll[id].src == src &&
	    wm8994->fll[id].in == freq_in && wm8994->fll[id].out == freq_out)
		return 0;

	/* If we're stopping the FLL redo the old config - no
	 * registers will actually be written but we avoid GCC flow
	 * analysis bugs spewing warnings.
	 */
	if (freq_out)
		ret = wm8994_get_fll_config(control, &fll, freq_in, freq_out);
	else
		ret = wm8994_get_fll_config(control, &fll, wm8994->fll[id].in,
					    wm8994->fll[id].out);
	if (ret < 0)
		return ret;

	/* Make sure that we're not providing SYSCLK right now */
	clk1 = snd_soc_component_read32(component, WM8994_CLOCKING_1);
	if (clk1 & WM8994_SYSCLK_SRC)
		aif_reg = WM8994_AIF2_CLOCKING_1;
	else
		aif_reg = WM8994_AIF1_CLOCKING_1;
	reg = snd_soc_component_read32(component, aif_reg);

	if ((reg & WM8994_AIF1CLK_ENA) &&
	    (reg & WM8994_AIF1CLK_SRC_MASK) == aif_src) {
		dev_err(component->dev, "FLL%d is currently providing SYSCLK\n",
			id + 1);
		return -EBUSY;
	}

	/* We always need to disable the FLL while reconfiguring */
	snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_1 + reg_offset,
			    WM8994_FLL1_ENA, 0);

	if (wm8994->fll_byp && src == WM8994_FLL_SRC_BCLK &&
	    freq_in == freq_out && freq_out) {
		dev_dbg(component->dev, "Bypassing FLL%d\n", id + 1);
		snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_5 + reg_offset,
				    WM8958_FLL1_BYP, WM8958_FLL1_BYP);
		goto out;
	}

	reg = (fll.outdiv << WM8994_FLL1_OUTDIV_SHIFT) |
		(fll.fll_fratio << WM8994_FLL1_FRATIO_SHIFT);
	snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_2 + reg_offset,
			    WM8994_FLL1_OUTDIV_MASK |
			    WM8994_FLL1_FRATIO_MASK, reg);

	snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_3 + reg_offset,
			    WM8994_FLL1_K_MASK, fll.k);

	snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_4 + reg_offset,
			    WM8994_FLL1_N_MASK,
			    fll.n << WM8994_FLL1_N_SHIFT);

	if (fll.lambda) {
		snd_soc_component_update_bits(component, WM8958_FLL1_EFS_1 + reg_offset,
				    WM8958_FLL1_LAMBDA_MASK,
				    fll.lambda);
		snd_soc_component_update_bits(component, WM8958_FLL1_EFS_2 + reg_offset,
				    WM8958_FLL1_EFS_ENA, WM8958_FLL1_EFS_ENA);
	} else {
		snd_soc_component_update_bits(component, WM8958_FLL1_EFS_2 + reg_offset,
				    WM8958_FLL1_EFS_ENA, 0);
	}

	snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_5 + reg_offset,
			    WM8994_FLL1_FRC_NCO | WM8958_FLL1_BYP |
			    WM8994_FLL1_REFCLK_DIV_MASK |
			    WM8994_FLL1_REFCLK_SRC_MASK,
			    ((src == WM8994_FLL_SRC_INTERNAL)
			     << WM8994_FLL1_FRC_NCO_SHIFT) |
			    (fll.clk_ref_div << WM8994_FLL1_REFCLK_DIV_SHIFT) |
			    (src - 1));

	/* Clear any pending completion from a previous failure */
	try_wait_for_completion(&wm8994->fll_locked[id]);

	/* Enable (with fractional mode if required) */
	if (freq_out) {
		/* Enable VMID if we need it */
		if (!was_enabled) {
			active_reference(component);

			switch (control->type) {
			case WM8994:
				vmid_reference(component);
				break;
			case WM8958:
				if (control->revision < 1)
					vmid_reference(component);
				break;
			default:
				break;
			}
		}

		reg = WM8994_FLL1_ENA;

		if (fll.k)
			reg |= WM8994_FLL1_FRAC;
		if (src == WM8994_FLL_SRC_INTERNAL)
			reg |= WM8994_FLL1_OSC_ENA;

		snd_soc_component_update_bits(component, WM8994_FLL1_CONTROL_1 + reg_offset,
				    WM8994_FLL1_ENA | WM8994_FLL1_OSC_ENA |
				    WM8994_FLL1_FRAC, reg);

		if (wm8994->fll_locked_irq) {
			timeout = wait_for_completion_timeout(&wm8994->fll_locked[id],
							      msecs_to_jiffies(10));
			if (timeout == 0)
				dev_warn(component->dev,
					 "Timed out waiting for FLL lock\n");
		} else {
			msleep(5);
		}
	} else {
		if (was_enabled) {
			switch (control->type) {
			case WM8994:
				vmid_dereference(component);
				break;
			case WM8958:
				if (control->revision < 1)
					vmid_dereference(component);
				break;
			default:
				break;
			}

			active_dereference(component);
		}
	}

out:
	wm8994->fll[id].in = freq_in;
	wm8994->fll[id].out = freq_out;
	wm8994->fll[id].src = src;

	configure_clock(component);

	/*
	 * If SYSCLK will be less than 50kHz adjust AIFnCLK dividers
	 * for detection.
	 */
	if (max(wm8994->aifclk[0], wm8994->aifclk[1]) < 50000) {
		dev_dbg(component->dev, "Configuring AIFs for 128fs\n");

		wm8994->aifdiv[0] = snd_soc_component_read32(component, WM8994_AIF1_RATE)
			& WM8994_AIF1CLK_RATE_MASK;
		wm8994->aifdiv[1] = snd_soc_component_read32(component, WM8994_AIF2_RATE)
			& WM8994_AIF1CLK_RATE_MASK;

		snd_soc_component_update_bits(component, WM8994_AIF1_RATE,
				    WM8994_AIF1CLK_RATE_MASK, 0x1);
		snd_soc_component_update_bits(component, WM8994_AIF2_RATE,
				    WM8994_AIF2CLK_RATE_MASK, 0x1);
	} else if (wm8994->aifdiv[0]) {
		snd_soc_component_update_bits(component, WM8994_AIF1_RATE,
				    WM8994_AIF1CLK_RATE_MASK,
				    wm8994->aifdiv[0]);
		snd_soc_component_update_bits(component, WM8994_AIF2_RATE,
				    WM8994_AIF2CLK_RATE_MASK,
				    wm8994->aifdiv[1]);

		wm8994->aifdiv[0] = 0;
		wm8994->aifdiv[1] = 0;
	}

	return 0;
}