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
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct dma_chan* rsnd_mod_dma_req (struct rsnd_dai_stream*,struct rsnd_mod*) ; 

__attribute__((used)) static struct dma_chan *rsnd_dmaen_request_channel(struct rsnd_dai_stream *io,
						   struct rsnd_mod *mod_from,
						   struct rsnd_mod *mod_to)
{
	if ((!mod_from && !mod_to) ||
	    (mod_from && mod_to))
		return NULL;

	if (mod_from)
		return rsnd_mod_dma_req(io, mod_from);
	else
		return rsnd_mod_dma_req(io, mod_to);
}