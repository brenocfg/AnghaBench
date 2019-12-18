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
struct wm8996_priv {int fll_src; unsigned int fll_fref; unsigned int fll_fout; int /*<<< orphan*/  fll_lock; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct i2c_client {scalar_t__ irq; } ;
struct _fll_div {int fll_refclk_div; int fll_ref_freq; int theta; int lambda; int fll_outdiv; int fll_fratio; int n; int fll_loop_gain; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
#define  WM8996_FLL_BCLK1 131 
 int /*<<< orphan*/  WM8996_FLL_CONTROL_1 ; 
 int /*<<< orphan*/  WM8996_FLL_CONTROL_2 ; 
 int /*<<< orphan*/  WM8996_FLL_CONTROL_3 ; 
 int /*<<< orphan*/  WM8996_FLL_CONTROL_4 ; 
 int /*<<< orphan*/  WM8996_FLL_CONTROL_5 ; 
 int /*<<< orphan*/  WM8996_FLL_CONTROL_6 ; 
#define  WM8996_FLL_DACLRCLK1 130 
 int /*<<< orphan*/  WM8996_FLL_EFS_1 ; 
 int /*<<< orphan*/  WM8996_FLL_EFS_2 ; 
 int WM8996_FLL_EFS_ENA ; 
 int WM8996_FLL_ENA ; 
 int WM8996_FLL_FRATIO_MASK ; 
 int WM8996_FLL_LFSR_SEL_SHIFT ; 
 int WM8996_FLL_LOCK_STS ; 
 int WM8996_FLL_LOOP_GAIN_MASK ; 
#define  WM8996_FLL_MCLK1 129 
#define  WM8996_FLL_MCLK2 128 
 int WM8996_FLL_N_MASK ; 
 int WM8996_FLL_N_SHIFT ; 
 int WM8996_FLL_OUTDIV_MASK ; 
 int WM8996_FLL_OUTDIV_SHIFT ; 
 int WM8996_FLL_REFCLK_DIV_MASK ; 
 int WM8996_FLL_REFCLK_DIV_SHIFT ; 
 int WM8996_FLL_REFCLK_SRC_MASK ; 
 int WM8996_FLL_REF_FREQ ; 
 int WM8996_FLL_REF_FREQ_SHIFT ; 
 int WM8996_FLL_SWITCH_CLK ; 
 int /*<<< orphan*/  WM8996_INTERRUPT_RAW_STATUS_2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int fll_factors (struct _fll_div*,unsigned int,unsigned int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 struct wm8996_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_wait_for_completion (int /*<<< orphan*/ *) ; 
 unsigned long usecs_to_jiffies (int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wm8996_bg_disable (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8996_bg_enable (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8996_set_fll(struct snd_soc_component *component, int fll_id, int source,
			  unsigned int Fref, unsigned int Fout)
{
	struct wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	struct i2c_client *i2c = to_i2c_client(component->dev);
	struct _fll_div fll_div;
	unsigned long timeout, time_left;
	int ret, reg, retry;

	/* Any change? */
	if (source == wm8996->fll_src && Fref == wm8996->fll_fref &&
	    Fout == wm8996->fll_fout)
		return 0;

	if (Fout == 0) {
		dev_dbg(component->dev, "FLL disabled\n");

		wm8996->fll_fref = 0;
		wm8996->fll_fout = 0;

		snd_soc_component_update_bits(component, WM8996_FLL_CONTROL_1,
				    WM8996_FLL_ENA, 0);

		wm8996_bg_disable(component);

		return 0;
	}

	ret = fll_factors(&fll_div, Fref, Fout);
	if (ret != 0)
		return ret;

	switch (source) {
	case WM8996_FLL_MCLK1:
		reg = 0;
		break;
	case WM8996_FLL_MCLK2:
		reg = 1;
		break;
	case WM8996_FLL_DACLRCLK1:
		reg = 2;
		break;
	case WM8996_FLL_BCLK1:
		reg = 3;
		break;
	default:
		dev_err(component->dev, "Unknown FLL source %d\n", ret);
		return -EINVAL;
	}

	reg |= fll_div.fll_refclk_div << WM8996_FLL_REFCLK_DIV_SHIFT;
	reg |= fll_div.fll_ref_freq << WM8996_FLL_REF_FREQ_SHIFT;

	snd_soc_component_update_bits(component, WM8996_FLL_CONTROL_5,
			    WM8996_FLL_REFCLK_DIV_MASK | WM8996_FLL_REF_FREQ |
			    WM8996_FLL_REFCLK_SRC_MASK, reg);

	reg = 0;
	if (fll_div.theta || fll_div.lambda)
		reg |= WM8996_FLL_EFS_ENA | (3 << WM8996_FLL_LFSR_SEL_SHIFT);
	else
		reg |= 1 << WM8996_FLL_LFSR_SEL_SHIFT;
	snd_soc_component_write(component, WM8996_FLL_EFS_2, reg);

	snd_soc_component_update_bits(component, WM8996_FLL_CONTROL_2,
			    WM8996_FLL_OUTDIV_MASK |
			    WM8996_FLL_FRATIO_MASK,
			    (fll_div.fll_outdiv << WM8996_FLL_OUTDIV_SHIFT) |
			    (fll_div.fll_fratio));

	snd_soc_component_write(component, WM8996_FLL_CONTROL_3, fll_div.theta);

	snd_soc_component_update_bits(component, WM8996_FLL_CONTROL_4,
			    WM8996_FLL_N_MASK | WM8996_FLL_LOOP_GAIN_MASK,
			    (fll_div.n << WM8996_FLL_N_SHIFT) |
			    fll_div.fll_loop_gain);

	snd_soc_component_write(component, WM8996_FLL_EFS_1, fll_div.lambda);

	/* Enable the bandgap if it's not already enabled */
	ret = snd_soc_component_read32(component, WM8996_FLL_CONTROL_1);
	if (!(ret & WM8996_FLL_ENA))
		wm8996_bg_enable(component);

	/* Clear any pending completions (eg, from failed startups) */
	try_wait_for_completion(&wm8996->fll_lock);

	snd_soc_component_update_bits(component, WM8996_FLL_CONTROL_1,
			    WM8996_FLL_ENA, WM8996_FLL_ENA);

	/* The FLL supports live reconfiguration - kick that in case we were
	 * already enabled.
	 */
	snd_soc_component_write(component, WM8996_FLL_CONTROL_6, WM8996_FLL_SWITCH_CLK);

	/* Wait for the FLL to lock, using the interrupt if possible */
	if (Fref > 1000000)
		timeout = usecs_to_jiffies(300);
	else
		timeout = msecs_to_jiffies(2);

	/* Allow substantially longer if we've actually got the IRQ, poll
	 * at a slightly higher rate if we don't.
	 */
	if (i2c->irq)
		timeout *= 10;
	else
		/* ensure timeout of atleast 1 jiffies */
		timeout = timeout/2 ? : 1;

	for (retry = 0; retry < 10; retry++) {
		time_left = wait_for_completion_timeout(&wm8996->fll_lock,
							timeout);
		if (time_left != 0) {
			WARN_ON(!i2c->irq);
			ret = 1;
			break;
		}

		ret = snd_soc_component_read32(component, WM8996_INTERRUPT_RAW_STATUS_2);
		if (ret & WM8996_FLL_LOCK_STS)
			break;
	}
	if (retry == 10) {
		dev_err(component->dev, "Timed out waiting for FLL\n");
		ret = -ETIMEDOUT;
	}

	dev_dbg(component->dev, "FLL configured for %dHz->%dHz\n", Fref, Fout);

	wm8996->fll_fref = Fref;
	wm8996->fll_fout = Fout;
	wm8996->fll_src = source;

	return ret;
}