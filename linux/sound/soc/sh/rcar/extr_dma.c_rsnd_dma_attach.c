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
struct rsnd_mod {int /*<<< orphan*/  type; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int rsnd_dai_connect (struct rsnd_mod*,struct rsnd_dai_stream*,int /*<<< orphan*/ ) ; 
 int rsnd_dma_alloc (struct rsnd_dai_stream*,struct rsnd_mod*,struct rsnd_mod**) ; 

int rsnd_dma_attach(struct rsnd_dai_stream *io, struct rsnd_mod *mod,
		    struct rsnd_mod **dma_mod)
{
	if (!(*dma_mod)) {
		int ret = rsnd_dma_alloc(io, mod, dma_mod);

		if (ret < 0)
			return ret;
	}

	return rsnd_dai_connect(*dma_mod, io, (*dma_mod)->type);
}