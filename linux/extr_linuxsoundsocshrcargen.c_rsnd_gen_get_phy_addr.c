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
struct rsnd_gen {int /*<<< orphan*/ * res; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 struct rsnd_gen* rsnd_priv_to_gen (struct rsnd_priv*) ; 

phys_addr_t rsnd_gen_get_phy_addr(struct rsnd_priv *priv, int reg_id)
{
	struct rsnd_gen *gen = rsnd_priv_to_gen(priv);

	return	gen->res[reg_id];
}