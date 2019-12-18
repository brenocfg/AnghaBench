#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rsnd_mod {TYPE_1__* ops; } ;
struct rsnd_dai_stream {int dummy; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {struct dma_chan* (* dma_req ) (struct rsnd_dai_stream*,struct rsnd_mod*) ;} ;

/* Variables and functions */
 struct dma_chan* stub1 (struct rsnd_dai_stream*,struct rsnd_mod*) ; 

struct dma_chan *rsnd_mod_dma_req(struct rsnd_dai_stream *io,
				  struct rsnd_mod *mod)
{
	if (!mod || !mod->ops || !mod->ops->dma_req)
		return NULL;

	return mod->ops->dma_req(io, mod);
}