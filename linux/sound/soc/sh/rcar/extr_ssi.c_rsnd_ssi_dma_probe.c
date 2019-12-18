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
struct rsnd_dai_stream {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int rsnd_dma_attach (struct rsnd_dai_stream*,struct rsnd_mod*,int /*<<< orphan*/ *) ; 
 int rsnd_ssi_common_probe (struct rsnd_mod*,struct rsnd_dai_stream*,struct rsnd_priv*) ; 
 scalar_t__ rsnd_ssi_is_multi_slave (struct rsnd_mod*,struct rsnd_dai_stream*) ; 

__attribute__((used)) static int rsnd_ssi_dma_probe(struct rsnd_mod *mod,
			      struct rsnd_dai_stream *io,
			      struct rsnd_priv *priv)
{
	int ret;

	/*
	 * SSIP/SSIU/IRQ/DMA are not needed on
	 * SSI Multi slaves
	 */
	if (rsnd_ssi_is_multi_slave(mod, io))
		return 0;

	ret = rsnd_ssi_common_probe(mod, io, priv);
	if (ret)
		return ret;

	/* SSI probe might be called many times in MUX multi path */
	ret = rsnd_dma_attach(io, mod, &io->dma);

	return ret;
}