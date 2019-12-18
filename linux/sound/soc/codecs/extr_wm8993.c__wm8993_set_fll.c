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
struct wm8993_priv {unsigned int fll_fref; unsigned int fll_fout; int fll_src; int /*<<< orphan*/  fll_lock; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct i2c_client {scalar_t__ irq; } ;
struct _fll_div {int k; int fll_outdiv; int fll_fratio; int n; int fll_clk_ref_div; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM8993_FLL_BCLK 130 
 int WM8993_FLL_CLK_REF_DIV_MASK ; 
 int WM8993_FLL_CLK_REF_DIV_SHIFT ; 
 int WM8993_FLL_CLK_SRC_MASK ; 
 int /*<<< orphan*/  WM8993_FLL_CONTROL_1 ; 
 int /*<<< orphan*/  WM8993_FLL_CONTROL_2 ; 
 int /*<<< orphan*/  WM8993_FLL_CONTROL_3 ; 
 int /*<<< orphan*/  WM8993_FLL_CONTROL_4 ; 
 int /*<<< orphan*/  WM8993_FLL_CONTROL_5 ; 
 int WM8993_FLL_ENA ; 
 int WM8993_FLL_FRAC_MASK ; 
 int WM8993_FLL_FRATIO_SHIFT ; 
#define  WM8993_FLL_LRCLK 129 
#define  WM8993_FLL_MCLK 128 
 int WM8993_FLL_N_MASK ; 
 int WM8993_FLL_N_SHIFT ; 
 int WM8993_FLL_OUTDIV_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int fll_factors (struct _fll_div*,unsigned int,unsigned int) ; 
 unsigned int msecs_to_jiffies (int) ; 
 struct wm8993_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_wait_for_completion (int /*<<< orphan*/ *) ; 
 unsigned int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int _wm8993_set_fll(struct snd_soc_component *component, int fll_id, int source,
			  unsigned int Fref, unsigned int Fout)
{
	struct wm8993_priv *wm8993 = snd_soc_component_get_drvdata(component);
	struct i2c_client *i2c = to_i2c_client(component->dev);
	u16 reg1, reg4, reg5;
	struct _fll_div fll_div;
	unsigned int timeout;
	int ret;

	/* Any change? */
	if (Fref == wm8993->fll_fref && Fout == wm8993->fll_fout)
		return 0;

	/* Disable the FLL */
	if (Fout == 0) {
		dev_dbg(component->dev, "FLL disabled\n");
		wm8993->fll_fref = 0;
		wm8993->fll_fout = 0;

		reg1 = snd_soc_component_read32(component, WM8993_FLL_CONTROL_1);
		reg1 &= ~WM8993_FLL_ENA;
		snd_soc_component_write(component, WM8993_FLL_CONTROL_1, reg1);

		return 0;
	}

	ret = fll_factors(&fll_div, Fref, Fout);
	if (ret != 0)
		return ret;

	reg5 = snd_soc_component_read32(component, WM8993_FLL_CONTROL_5);
	reg5 &= ~WM8993_FLL_CLK_SRC_MASK;

	switch (fll_id) {
	case WM8993_FLL_MCLK:
		break;

	case WM8993_FLL_LRCLK:
		reg5 |= 1;
		break;

	case WM8993_FLL_BCLK:
		reg5 |= 2;
		break;

	default:
		dev_err(component->dev, "Unknown FLL ID %d\n", fll_id);
		return -EINVAL;
	}

	/* Any FLL configuration change requires that the FLL be
	 * disabled first. */
	reg1 = snd_soc_component_read32(component, WM8993_FLL_CONTROL_1);
	reg1 &= ~WM8993_FLL_ENA;
	snd_soc_component_write(component, WM8993_FLL_CONTROL_1, reg1);

	/* Apply the configuration */
	if (fll_div.k)
		reg1 |= WM8993_FLL_FRAC_MASK;
	else
		reg1 &= ~WM8993_FLL_FRAC_MASK;
	snd_soc_component_write(component, WM8993_FLL_CONTROL_1, reg1);

	snd_soc_component_write(component, WM8993_FLL_CONTROL_2,
		      (fll_div.fll_outdiv << WM8993_FLL_OUTDIV_SHIFT) |
		      (fll_div.fll_fratio << WM8993_FLL_FRATIO_SHIFT));
	snd_soc_component_write(component, WM8993_FLL_CONTROL_3, fll_div.k);

	reg4 = snd_soc_component_read32(component, WM8993_FLL_CONTROL_4);
	reg4 &= ~WM8993_FLL_N_MASK;
	reg4 |= fll_div.n << WM8993_FLL_N_SHIFT;
	snd_soc_component_write(component, WM8993_FLL_CONTROL_4, reg4);

	reg5 &= ~WM8993_FLL_CLK_REF_DIV_MASK;
	reg5 |= fll_div.fll_clk_ref_div << WM8993_FLL_CLK_REF_DIV_SHIFT;
	snd_soc_component_write(component, WM8993_FLL_CONTROL_5, reg5);

	/* If we've got an interrupt wired up make sure we get it */
	if (i2c->irq)
		timeout = msecs_to_jiffies(20);
	else if (Fref < 1000000)
		timeout = msecs_to_jiffies(3);
	else
		timeout = msecs_to_jiffies(1);

	try_wait_for_completion(&wm8993->fll_lock);

	/* Enable the FLL */
	snd_soc_component_write(component, WM8993_FLL_CONTROL_1, reg1 | WM8993_FLL_ENA);

	timeout = wait_for_completion_timeout(&wm8993->fll_lock, timeout);
	if (i2c->irq && !timeout)
		dev_warn(component->dev, "Timed out waiting for FLL\n");

	dev_dbg(component->dev, "FLL enabled at %dHz->%dHz\n", Fref, Fout);

	wm8993->fll_fref = Fref;
	wm8993->fll_fout = Fout;
	wm8993->fll_src = source;

	return 0;
}