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
struct wm8962_priv {int fll_src; unsigned int fll_fref; unsigned int fll_fout; scalar_t__ irq; int /*<<< orphan*/  fll_lock; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct _fll_div {int fll_outdiv; int fll_refclk_div; int fll_fratio; scalar_t__ n; scalar_t__ lambda; scalar_t__ theta; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
#define  WM8962_FLL_BCLK 131 
 int /*<<< orphan*/  WM8962_FLL_CONTROL_1 ; 
 int /*<<< orphan*/  WM8962_FLL_CONTROL_2 ; 
 int /*<<< orphan*/  WM8962_FLL_CONTROL_3 ; 
 int /*<<< orphan*/  WM8962_FLL_CONTROL_5 ; 
 int /*<<< orphan*/  WM8962_FLL_CONTROL_6 ; 
 int /*<<< orphan*/  WM8962_FLL_CONTROL_7 ; 
 int /*<<< orphan*/  WM8962_FLL_CONTROL_8 ; 
 int WM8962_FLL_ENA ; 
 int WM8962_FLL_FRAC ; 
 int WM8962_FLL_FRATIO_MASK ; 
 int WM8962_FLL_FRC_NCO ; 
#define  WM8962_FLL_INT 130 
#define  WM8962_FLL_MCLK 129 
#define  WM8962_FLL_OSC 128 
 int WM8962_FLL_OSC_ENA ; 
 int WM8962_FLL_OUTDIV_MASK ; 
 int WM8962_FLL_OUTDIV_SHIFT ; 
 int WM8962_FLL_REFCLK_DIV_MASK ; 
 int WM8962_FLL_REFCLK_SRC_MASK ; 
 int WM8962_FLL_REFCLK_SRC_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int fll_factors (struct _fll_div*,unsigned int,unsigned int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct wm8962_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int wm8962_set_fll(struct snd_soc_component *component, int fll_id, int source,
			  unsigned int Fref, unsigned int Fout)
{
	struct wm8962_priv *wm8962 = snd_soc_component_get_drvdata(component);
	struct _fll_div fll_div;
	unsigned long timeout;
	int ret;
	int fll1 = 0;

	/* Any change? */
	if (source == wm8962->fll_src && Fref == wm8962->fll_fref &&
	    Fout == wm8962->fll_fout)
		return 0;

	if (Fout == 0) {
		dev_dbg(component->dev, "FLL disabled\n");

		wm8962->fll_fref = 0;
		wm8962->fll_fout = 0;

		snd_soc_component_update_bits(component, WM8962_FLL_CONTROL_1,
				    WM8962_FLL_ENA, 0);

		pm_runtime_put(component->dev);

		return 0;
	}

	ret = fll_factors(&fll_div, Fref, Fout);
	if (ret != 0)
		return ret;

	/* Parameters good, disable so we can reprogram */
	snd_soc_component_update_bits(component, WM8962_FLL_CONTROL_1, WM8962_FLL_ENA, 0);

	switch (fll_id) {
	case WM8962_FLL_MCLK:
	case WM8962_FLL_BCLK:
	case WM8962_FLL_OSC:
		fll1 |= (fll_id - 1) << WM8962_FLL_REFCLK_SRC_SHIFT;
		break;
	case WM8962_FLL_INT:
		snd_soc_component_update_bits(component, WM8962_FLL_CONTROL_1,
				    WM8962_FLL_OSC_ENA, WM8962_FLL_OSC_ENA);
		snd_soc_component_update_bits(component, WM8962_FLL_CONTROL_5,
				    WM8962_FLL_FRC_NCO, WM8962_FLL_FRC_NCO);
		break;
	default:
		dev_err(component->dev, "Unknown FLL source %d\n", ret);
		return -EINVAL;
	}

	if (fll_div.theta || fll_div.lambda)
		fll1 |= WM8962_FLL_FRAC;

	/* Stop the FLL while we reconfigure */
	snd_soc_component_update_bits(component, WM8962_FLL_CONTROL_1, WM8962_FLL_ENA, 0);

	snd_soc_component_update_bits(component, WM8962_FLL_CONTROL_2,
			    WM8962_FLL_OUTDIV_MASK |
			    WM8962_FLL_REFCLK_DIV_MASK,
			    (fll_div.fll_outdiv << WM8962_FLL_OUTDIV_SHIFT) |
			    (fll_div.fll_refclk_div));

	snd_soc_component_update_bits(component, WM8962_FLL_CONTROL_3,
			    WM8962_FLL_FRATIO_MASK, fll_div.fll_fratio);

	snd_soc_component_write(component, WM8962_FLL_CONTROL_6, fll_div.theta);
	snd_soc_component_write(component, WM8962_FLL_CONTROL_7, fll_div.lambda);
	snd_soc_component_write(component, WM8962_FLL_CONTROL_8, fll_div.n);

	reinit_completion(&wm8962->fll_lock);

	ret = pm_runtime_get_sync(component->dev);
	if (ret < 0) {
		dev_err(component->dev, "Failed to resume device: %d\n", ret);
		return ret;
	}

	snd_soc_component_update_bits(component, WM8962_FLL_CONTROL_1,
			    WM8962_FLL_FRAC | WM8962_FLL_REFCLK_SRC_MASK |
			    WM8962_FLL_ENA, fll1 | WM8962_FLL_ENA);

	dev_dbg(component->dev, "FLL configured for %dHz->%dHz\n", Fref, Fout);

	/* This should be a massive overestimate but go even
	 * higher if we'll error out
	 */
	if (wm8962->irq)
		timeout = msecs_to_jiffies(5);
	else
		timeout = msecs_to_jiffies(1);

	timeout = wait_for_completion_timeout(&wm8962->fll_lock,
					      timeout);

	if (timeout == 0 && wm8962->irq) {
		dev_err(component->dev, "FLL lock timed out");
		snd_soc_component_update_bits(component, WM8962_FLL_CONTROL_1,
				    WM8962_FLL_ENA, 0);
		pm_runtime_put(component->dev);
		return -ETIMEDOUT;
	}

	wm8962->fll_fref = Fref;
	wm8962->fll_fout = Fout;
	wm8962->fll_src = source;

	return 0;
}