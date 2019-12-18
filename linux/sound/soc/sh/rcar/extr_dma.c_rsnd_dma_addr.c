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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  rsnd_gen2_dma_addr (struct rsnd_dai_stream*,struct rsnd_mod*,int,int) ; 
 struct rsnd_priv* rsnd_io_to_priv (struct rsnd_dai_stream*) ; 
 scalar_t__ rsnd_is_gen1 (struct rsnd_priv*) ; 

__attribute__((used)) static dma_addr_t rsnd_dma_addr(struct rsnd_dai_stream *io,
				struct rsnd_mod *mod,
				int is_play, int is_from)
{
	struct rsnd_priv *priv = rsnd_io_to_priv(io);

	/*
	 * gen1 uses default DMA addr
	 */
	if (rsnd_is_gen1(priv))
		return 0;

	if (!mod)
		return 0;

	return rsnd_gen2_dma_addr(io, mod, is_play, is_from);
}