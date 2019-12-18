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
struct wm_adsp {int num; int /*<<< orphan*/  base; int /*<<< orphan*/  regmap; } ;
struct madera_priv {unsigned int* adsp_rate_cache; struct madera* madera; struct wm_adsp* adsp; } ;
struct madera {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int MADERA_DSP_RATE_MASK ; 
 unsigned int MADERA_DSP_RATE_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  madera_spin_sysclk (struct madera_priv*) ; 
 int madera_write_adsp_clk_setting (struct madera_priv*,struct wm_adsp*,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

int madera_set_adsp_clk(struct madera_priv *priv, int dsp_num,
			unsigned int freq)
{
	struct wm_adsp *dsp = &priv->adsp[dsp_num];
	struct madera *madera = priv->madera;
	unsigned int cur, new;
	int ret;

	/*
	 * This is called at a higher DAPM priority than the mux widgets so
	 * the muxes are still off at this point and it's safe to change
	 * the rate domain control.
	 * Also called at a lower DAPM priority than the domain group widgets
	 * so locking the reads of adsp_rate_cache is not necessary as we know
	 * changes are locked out by the domain_group_ref reference count.
	 */

	ret = regmap_read(dsp->regmap,  dsp->base, &cur);
	if (ret) {
		dev_err(madera->dev,
			"Failed to read current DSP rate: %d\n", ret);
		return ret;
	}

	cur &= MADERA_DSP_RATE_MASK;

	new = priv->adsp_rate_cache[dsp->num - 1] << MADERA_DSP_RATE_SHIFT;

	if (new == cur) {
		dev_dbg(madera->dev, "DSP rate not changed\n");
		return madera_write_adsp_clk_setting(priv, dsp, freq);
	} else {
		dev_dbg(madera->dev, "DSP rate changed\n");

		/* The write must be guarded by a number of SYSCLK cycles */
		madera_spin_sysclk(priv);
		ret = madera_write_adsp_clk_setting(priv, dsp, freq);
		madera_spin_sysclk(priv);
		return ret;
	}
}