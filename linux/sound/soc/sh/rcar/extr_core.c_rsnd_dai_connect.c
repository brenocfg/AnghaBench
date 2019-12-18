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
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {struct rsnd_mod** mod; } ;
struct device {int dummy; } ;
typedef  enum rsnd_mod_type { ____Placeholder_rsnd_mod_type } rsnd_mod_type ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rsnd_io_is_play (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_mod_name (struct rsnd_mod*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 

int rsnd_dai_connect(struct rsnd_mod *mod,
		     struct rsnd_dai_stream *io,
		     enum rsnd_mod_type type)
{
	struct rsnd_priv *priv;
	struct device *dev;

	if (!mod)
		return -EIO;

	if (io->mod[type] == mod)
		return 0;

	if (io->mod[type])
		return -EINVAL;

	priv = rsnd_mod_to_priv(mod);
	dev = rsnd_priv_to_dev(priv);

	io->mod[type] = mod;

	dev_dbg(dev, "%s is connected to io (%s)\n",
		rsnd_mod_name(mod),
		rsnd_io_is_play(io) ? "Playback" : "Capture");

	return 0;
}