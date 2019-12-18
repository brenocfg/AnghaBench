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
struct rsnd_dma {int /*<<< orphan*/  mod_to; int /*<<< orphan*/  mod_from; } ;
struct rsnd_dai_stream {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct rsnd_dmaen* rsnd_dma_to_dmaen (struct rsnd_dma*) ; 
 int /*<<< orphan*/ * rsnd_dmaen_request_channel (struct rsnd_dai_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rsnd_dma* rsnd_mod_to_dma (struct rsnd_mod*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 

__attribute__((used)) static int rsnd_dmaen_prepare(struct rsnd_mod *mod,
			      struct rsnd_dai_stream *io,
			      struct rsnd_priv *priv)
{
	struct rsnd_dma *dma = rsnd_mod_to_dma(mod);
	struct rsnd_dmaen *dmaen = rsnd_dma_to_dmaen(dma);
	struct device *dev = rsnd_priv_to_dev(priv);

	/* maybe suspended */
	if (dmaen->chan)
		return 0;

	/*
	 * DMAEngine request uses mutex lock.
	 * Thus, it shouldn't be called under spinlock.
	 * Let's call it under prepare
	 */
	dmaen->chan = rsnd_dmaen_request_channel(io,
						 dma->mod_from,
						 dma->mod_to);
	if (IS_ERR_OR_NULL(dmaen->chan)) {
		dmaen->chan = NULL;
		dev_err(dev, "can't get dma channel\n");
		return -EIO;
	}

	return 0;
}