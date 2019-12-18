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
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct dma_chan* rsnd_dma_request_channel (int /*<<< orphan*/ ,struct rsnd_mod*,char*) ; 
 int rsnd_io_is_play (struct rsnd_dai_stream*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_ssiu_of_node (struct rsnd_priv*) ; 

__attribute__((used)) static struct dma_chan *rsnd_ssiu_dma_req(struct rsnd_dai_stream *io,
					  struct rsnd_mod *mod)
{
	struct rsnd_priv *priv = rsnd_mod_to_priv(mod);
	int is_play = rsnd_io_is_play(io);
	char *name;

	/*
	 * It should use "rcar_sound,ssiu" on DT.
	 * But, we need to keep compatibility for old version.
	 *
	 * If it has "rcar_sound.ssiu", it will be used.
	 * If not, "rcar_sound.ssi" will be used.
	 * see
	 *	rsnd_ssi_dma_req()
	 *	rsnd_dma_of_path()
	 */

	name = is_play ? "rx" : "tx";

	return rsnd_dma_request_channel(rsnd_ssiu_of_node(priv),
					mod, name);
}