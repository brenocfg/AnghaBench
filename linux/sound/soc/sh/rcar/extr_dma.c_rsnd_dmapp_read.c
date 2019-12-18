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
typedef  int /*<<< orphan*/  u32 ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dma_ctrl {int dummy; } ;
struct rsnd_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_dmapp_addr (struct rsnd_dma_ctrl*,struct rsnd_dma*,int /*<<< orphan*/ ) ; 
 struct rsnd_mod* rsnd_mod_get (struct rsnd_dma*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 struct rsnd_dma_ctrl* rsnd_priv_to_dmac (struct rsnd_priv*) ; 

__attribute__((used)) static u32 rsnd_dmapp_read(struct rsnd_dma *dma, u32 reg)
{
	struct rsnd_mod *mod = rsnd_mod_get(dma);
	struct rsnd_priv *priv = rsnd_mod_to_priv(mod);
	struct rsnd_dma_ctrl *dmac = rsnd_priv_to_dmac(priv);

	return ioread32(rsnd_dmapp_addr(dmac, dma, reg));
}