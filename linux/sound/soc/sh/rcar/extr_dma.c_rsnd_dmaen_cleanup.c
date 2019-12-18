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
struct rsnd_dmaen {int /*<<< orphan*/ * chan; } ;
struct rsnd_dma {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 struct rsnd_dmaen* rsnd_dma_to_dmaen (struct rsnd_dma*) ; 
 struct rsnd_dma* rsnd_mod_to_dma (struct rsnd_mod*) ; 

__attribute__((used)) static int rsnd_dmaen_cleanup(struct rsnd_mod *mod,
			      struct rsnd_dai_stream *io,
			      struct rsnd_priv *priv)
{
	struct rsnd_dma *dma = rsnd_mod_to_dma(mod);
	struct rsnd_dmaen *dmaen = rsnd_dma_to_dmaen(dma);

	/*
	 * DMAEngine release uses mutex lock.
	 * Thus, it shouldn't be called under spinlock.
	 * Let's call it under prepare
	 */
	if (dmaen->chan)
		dma_release_channel(dmaen->chan);

	dmaen->chan = NULL;

	return 0;
}