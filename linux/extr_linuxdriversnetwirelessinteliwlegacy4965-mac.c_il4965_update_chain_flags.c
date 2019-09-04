#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rx_chain; } ;
struct TYPE_5__ {scalar_t__ rx_chain; } ;
struct il_priv {TYPE_3__ staging; TYPE_2__ active; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_rxon_chain ) (struct il_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  il_commit_rxon (struct il_priv*) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*) ; 

void
il4965_update_chain_flags(struct il_priv *il)
{
	if (il->ops->set_rxon_chain) {
		il->ops->set_rxon_chain(il);
		if (il->active.rx_chain != il->staging.rx_chain)
			il_commit_rxon(il);
	}
}