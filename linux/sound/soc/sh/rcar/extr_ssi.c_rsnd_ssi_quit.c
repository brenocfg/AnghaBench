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
struct rsnd_ssi {scalar_t__ wsr; scalar_t__ cr_mode; scalar_t__ cr_own; int /*<<< orphan*/  usrcnt; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_mod_name (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_power_off (struct rsnd_mod*) ; 
 struct rsnd_ssi* rsnd_mod_to_ssi (struct rsnd_mod*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_ssi_is_run_mods (struct rsnd_mod*,struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_ssi_master_clk_stop (struct rsnd_mod*,struct rsnd_dai_stream*) ; 

__attribute__((used)) static int rsnd_ssi_quit(struct rsnd_mod *mod,
			 struct rsnd_dai_stream *io,
			 struct rsnd_priv *priv)
{
	struct rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);
	struct device *dev = rsnd_priv_to_dev(priv);

	if (!rsnd_ssi_is_run_mods(mod, io))
		return 0;

	if (!ssi->usrcnt) {
		dev_err(dev, "%s usrcnt error\n", rsnd_mod_name(mod));
		return -EIO;
	}

	rsnd_ssi_master_clk_stop(mod, io);

	rsnd_mod_power_off(mod);

	ssi->usrcnt--;

	if (!ssi->usrcnt) {
		ssi->cr_own	= 0;
		ssi->cr_mode	= 0;
		ssi->wsr	= 0;
	}

	return 0;
}