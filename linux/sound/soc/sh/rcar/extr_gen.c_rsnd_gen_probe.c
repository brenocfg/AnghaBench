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
struct rsnd_priv {struct rsnd_gen* gen; } ;
struct rsnd_gen {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct rsnd_gen* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int rsnd_gen1_probe (struct rsnd_priv*) ; 
 int rsnd_gen2_probe (struct rsnd_priv*) ; 
 scalar_t__ rsnd_is_gen1 (struct rsnd_priv*) ; 
 scalar_t__ rsnd_is_gen2 (struct rsnd_priv*) ; 
 scalar_t__ rsnd_is_gen3 (struct rsnd_priv*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 

int rsnd_gen_probe(struct rsnd_priv *priv)
{
	struct device *dev = rsnd_priv_to_dev(priv);
	struct rsnd_gen *gen;
	int ret;

	gen = devm_kzalloc(dev, sizeof(*gen), GFP_KERNEL);
	if (!gen)
		return -ENOMEM;

	priv->gen = gen;

	ret = -ENODEV;
	if (rsnd_is_gen1(priv))
		ret = rsnd_gen1_probe(priv);
	else if (rsnd_is_gen2(priv) ||
		 rsnd_is_gen3(priv))
		ret = rsnd_gen2_probe(priv);

	if (ret < 0)
		dev_err(dev, "unknown generation R-Car sound device\n");

	return ret;
}