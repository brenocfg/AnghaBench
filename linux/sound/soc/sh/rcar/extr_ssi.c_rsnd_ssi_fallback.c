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
struct rsnd_mod {int /*<<< orphan*/ * ops; } ;
struct rsnd_dai_stream {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_mod_name (struct rsnd_mod*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_ssi_pio_ops ; 

__attribute__((used)) static int rsnd_ssi_fallback(struct rsnd_mod *mod,
			     struct rsnd_dai_stream *io,
			     struct rsnd_priv *priv)
{
	struct device *dev = rsnd_priv_to_dev(priv);

	/*
	 * fallback to PIO
	 *
	 * SSI .probe might be called again.
	 * see
	 *	rsnd_rdai_continuance_probe()
	 */
	mod->ops = &rsnd_ssi_pio_ops;

	dev_info(dev, "%s fallback to PIO mode\n", rsnd_mod_name(mod));

	return 0;
}