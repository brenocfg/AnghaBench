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
struct wm5100_priv {struct wm5100_fll* fll; } ;
struct wm5100_fll {int fout; int src; unsigned int fref; int /*<<< orphan*/  lock; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct i2c_client {scalar_t__ irq; } ;
struct _fll_div {int fll_outdiv; int fll_fratio; int theta; int n; int fll_refclk_div; int lambda; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int WM5100_CLOCKING_3 ; 
#define  WM5100_FLL1 136 
 int /*<<< orphan*/  WM5100_FLL1_CONTROL_1 ; 
 int WM5100_FLL1_ENA ; 
 int WM5100_FLL1_FRATIO_MASK ; 
 int WM5100_FLL1_LAMBDA_MASK ; 
 int WM5100_FLL1_LOCK_STS ; 
 int WM5100_FLL1_N_MASK ; 
 int WM5100_FLL1_OUTDIV_MASK ; 
 int WM5100_FLL1_OUTDIV_SHIFT ; 
 int WM5100_FLL1_REFCLK_DIV_MASK ; 
 int WM5100_FLL1_REFCLK_DIV_SHIFT ; 
 int WM5100_FLL1_REFCLK_SRC_MASK ; 
 int WM5100_FLL1_THETA_MASK ; 
#define  WM5100_FLL2 135 
 int /*<<< orphan*/  WM5100_FLL2_CONTROL_2 ; 
 int WM5100_FLL2_LOCK_STS ; 
#define  WM5100_FLL_SRC_AIF1BCLK 134 
#define  WM5100_FLL_SRC_AIF2BCLK 133 
#define  WM5100_FLL_SRC_AIF3BCLK 132 
#define  WM5100_FLL_SRC_FLL1 131 
#define  WM5100_FLL_SRC_FLL2 130 
#define  WM5100_FLL_SRC_MCLK1 129 
#define  WM5100_FLL_SRC_MCLK2 128 
 int /*<<< orphan*/  WM5100_INTERRUPT_RAW_STATUS_3 ; 
 int WM5100_SYSCLK_ENA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int fll_factors (struct _fll_div*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct wm5100_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_wait_for_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm5100_set_fll(struct snd_soc_component *component, int fll_id, int source,
			  unsigned int Fref, unsigned int Fout)
{
	struct i2c_client *i2c = to_i2c_client(component->dev);
	struct wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	struct _fll_div factors;
	struct wm5100_fll *fll;
	int ret, base, lock, i, timeout;
	unsigned long time_left;

	switch (fll_id) {
	case WM5100_FLL1:
		fll = &wm5100->fll[0];
		base = WM5100_FLL1_CONTROL_1 - 1;
		lock = WM5100_FLL1_LOCK_STS;
		break;
	case WM5100_FLL2:
		fll = &wm5100->fll[1];
		base = WM5100_FLL2_CONTROL_2 - 1;
		lock = WM5100_FLL2_LOCK_STS;
		break;
	default:
		dev_err(component->dev, "Unknown FLL %d\n",fll_id);
		return -EINVAL;
	}

	if (!Fout) {
		dev_dbg(component->dev, "FLL%d disabled", fll_id);
		if (fll->fout)
			pm_runtime_put(component->dev);
		fll->fout = 0;
		snd_soc_component_update_bits(component, base + 1, WM5100_FLL1_ENA, 0);
		return 0;
	}

	switch (source) {
	case WM5100_FLL_SRC_MCLK1:
	case WM5100_FLL_SRC_MCLK2:
	case WM5100_FLL_SRC_FLL1:
	case WM5100_FLL_SRC_FLL2:
	case WM5100_FLL_SRC_AIF1BCLK:
	case WM5100_FLL_SRC_AIF2BCLK:
	case WM5100_FLL_SRC_AIF3BCLK:
		break;
	default:
		dev_err(component->dev, "Invalid FLL source %d\n", source);
		return -EINVAL;
	}

	ret = fll_factors(&factors, Fref, Fout);
	if (ret < 0)
		return ret;

	/* Disable the FLL while we reconfigure */
	snd_soc_component_update_bits(component, base + 1, WM5100_FLL1_ENA, 0);

	snd_soc_component_update_bits(component, base + 2,
			    WM5100_FLL1_OUTDIV_MASK | WM5100_FLL1_FRATIO_MASK,
			    (factors.fll_outdiv << WM5100_FLL1_OUTDIV_SHIFT) |
			    factors.fll_fratio);
	snd_soc_component_update_bits(component, base + 3, WM5100_FLL1_THETA_MASK,
			    factors.theta);
	snd_soc_component_update_bits(component, base + 5, WM5100_FLL1_N_MASK, factors.n);
	snd_soc_component_update_bits(component, base + 6,
			    WM5100_FLL1_REFCLK_DIV_MASK |
			    WM5100_FLL1_REFCLK_SRC_MASK,
			    (factors.fll_refclk_div
			     << WM5100_FLL1_REFCLK_DIV_SHIFT) | source);
	snd_soc_component_update_bits(component, base + 7, WM5100_FLL1_LAMBDA_MASK,
			    factors.lambda);

	/* Clear any pending completions */
	try_wait_for_completion(&fll->lock);

	pm_runtime_get_sync(component->dev);

	snd_soc_component_update_bits(component, base + 1, WM5100_FLL1_ENA, WM5100_FLL1_ENA);

	if (i2c->irq)
		timeout = 2;
	else
		timeout = 50;

	snd_soc_component_update_bits(component, WM5100_CLOCKING_3, WM5100_SYSCLK_ENA,
			    WM5100_SYSCLK_ENA);

	/* Poll for the lock; will use interrupt when we can test */
	for (i = 0; i < timeout; i++) {
		if (i2c->irq) {
			time_left = wait_for_completion_timeout(&fll->lock,
							msecs_to_jiffies(25));
			if (time_left > 0)
				break;
		} else {
			msleep(1);
		}

		ret = snd_soc_component_read32(component,
				   WM5100_INTERRUPT_RAW_STATUS_3);
		if (ret < 0) {
			dev_err(component->dev,
				"Failed to read FLL status: %d\n",
				ret);
			continue;
		}
		if (ret & lock)
			break;
	}
	if (i == timeout) {
		dev_err(component->dev, "FLL%d lock timed out\n", fll_id);
		pm_runtime_put(component->dev);
		return -ETIMEDOUT;
	}

	fll->src = source;
	fll->fref = Fref;
	fll->fout = Fout;

	dev_dbg(component->dev, "FLL%d running %dHz->%dHz\n", fll_id,
		Fref, Fout);

	return 0;
}