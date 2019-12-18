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
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSND_MOD_SSIP ; 
 int /*<<< orphan*/  __rsnd_ssi_is_pin_sharing (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_dai_connect (int /*<<< orphan*/ ,struct rsnd_dai_stream*,int /*<<< orphan*/ ) ; 
 struct rsnd_dai* rsnd_io_to_rdai (struct rsnd_dai_stream*) ; 
 int rsnd_mod_id (struct rsnd_mod*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_rdai_is_clk_master (struct rsnd_dai*) ; 
 int /*<<< orphan*/  rsnd_ssi_mod_get (struct rsnd_priv*,int) ; 

__attribute__((used)) static void rsnd_ssi_parent_attach(struct rsnd_mod *mod,
				   struct rsnd_dai_stream *io)
{
	struct rsnd_dai *rdai = rsnd_io_to_rdai(io);
	struct rsnd_priv *priv = rsnd_mod_to_priv(mod);

	if (!__rsnd_ssi_is_pin_sharing(mod))
		return;

	if (!rsnd_rdai_is_clk_master(rdai))
		return;

	switch (rsnd_mod_id(mod)) {
	case 1:
	case 2:
	case 9:
		rsnd_dai_connect(rsnd_ssi_mod_get(priv, 0), io, RSND_MOD_SSIP);
		break;
	case 4:
		rsnd_dai_connect(rsnd_ssi_mod_get(priv, 3), io, RSND_MOD_SSIP);
		break;
	case 8:
		rsnd_dai_connect(rsnd_ssi_mod_get(priv, 7), io, RSND_MOD_SSIP);
		break;
	}
}