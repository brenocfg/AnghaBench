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
struct rsnd_priv {struct rsnd_adg* adg; } ;
struct rsnd_adg {int /*<<< orphan*/  mod; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  adg_ops ; 
 struct rsnd_adg* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_adg_clk_dbg_info (struct rsnd_priv*,struct rsnd_adg*) ; 
 int /*<<< orphan*/  rsnd_adg_clk_enable (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_adg_get_clkin (struct rsnd_priv*,struct rsnd_adg*) ; 
 int /*<<< orphan*/  rsnd_adg_get_clkout (struct rsnd_priv*,struct rsnd_adg*) ; 
 int rsnd_mod_init (struct rsnd_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 

int rsnd_adg_probe(struct rsnd_priv *priv)
{
	struct rsnd_adg *adg;
	struct device *dev = rsnd_priv_to_dev(priv);
	int ret;

	adg = devm_kzalloc(dev, sizeof(*adg), GFP_KERNEL);
	if (!adg)
		return -ENOMEM;

	ret = rsnd_mod_init(priv, &adg->mod, &adg_ops,
		      NULL, 0, 0);
	if (ret)
		return ret;

	rsnd_adg_get_clkin(priv, adg);
	rsnd_adg_get_clkout(priv, adg);
	rsnd_adg_clk_dbg_info(priv, adg);

	priv->adg = adg;

	rsnd_adg_clk_enable(priv);

	return 0;
}