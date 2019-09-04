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
struct rsnd_mod {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  rsnd_ssi_dma_ops ; 

int rsnd_ssi_is_dma_mode(struct rsnd_mod *mod)
{
	return mod->ops == &rsnd_ssi_dma_ops;
}