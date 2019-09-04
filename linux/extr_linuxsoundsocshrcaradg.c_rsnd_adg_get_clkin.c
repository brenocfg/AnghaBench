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
struct rsnd_priv {int dummy; } ;
struct rsnd_adg {struct clk** clk; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int CLKMAX ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/ * clk_name ; 
 struct clk* devm_clk_get (struct device*,int /*<<< orphan*/ ) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 

__attribute__((used)) static void rsnd_adg_get_clkin(struct rsnd_priv *priv,
			       struct rsnd_adg *adg)
{
	struct device *dev = rsnd_priv_to_dev(priv);
	struct clk *clk;
	int i;

	for (i = 0; i < CLKMAX; i++) {
		clk = devm_clk_get(dev, clk_name[i]);
		adg->clk[i] = IS_ERR(clk) ? NULL : clk;
	}
}