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
struct rsnd_mod {int /*<<< orphan*/  type; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 struct rsnd_mod* rsnd_cmd_mod_get (struct rsnd_priv*,int) ; 
 int rsnd_dai_connect (struct rsnd_mod*,struct rsnd_dai_stream*,int /*<<< orphan*/ ) ; 
 struct rsnd_priv* rsnd_io_to_priv (struct rsnd_dai_stream*) ; 

int rsnd_cmd_attach(struct rsnd_dai_stream *io, int id)
{
	struct rsnd_priv *priv = rsnd_io_to_priv(io);
	struct rsnd_mod *mod = rsnd_cmd_mod_get(priv, id);

	return rsnd_dai_connect(mod, io, mod->type);
}