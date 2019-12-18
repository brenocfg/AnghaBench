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
 int /*<<< orphan*/  rsnd_src_of_node (struct rsnd_priv*) ; 

__attribute__((used)) static struct dma_chan *rsnd_src_dma_req(struct rsnd_dai_stream *io,
					 struct rsnd_mod *mod)
{
	struct rsnd_priv *priv = rsnd_mod_to_priv(mod);
	int is_play = rsnd_io_is_play(io);

	return rsnd_dma_request_channel(rsnd_src_of_node(priv),
					mod,
					is_play ? "rx" : "tx");
}