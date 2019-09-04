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
struct rsnd_dma {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PDMACHCR ; 
 int PDMACHCR_DE ; 
 int /*<<< orphan*/  rsnd_dmapp_bset (struct rsnd_dma*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rsnd_dmapp_read (struct rsnd_dma*,int /*<<< orphan*/ ) ; 
 struct rsnd_dma* rsnd_mod_to_dma (struct rsnd_mod*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rsnd_dmapp_stop(struct rsnd_mod *mod,
			   struct rsnd_dai_stream *io,
			   struct rsnd_priv *priv)
{
	struct rsnd_dma *dma = rsnd_mod_to_dma(mod);
	int i;

	rsnd_dmapp_bset(dma, 0,  PDMACHCR_DE, PDMACHCR);

	for (i = 0; i < 1024; i++) {
		if (0 == (rsnd_dmapp_read(dma, PDMACHCR) & PDMACHCR_DE))
			return 0;
		udelay(1);
	}

	return -EIO;
}