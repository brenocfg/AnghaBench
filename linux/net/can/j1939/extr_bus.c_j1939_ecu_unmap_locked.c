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
struct j1939_priv {struct j1939_addr_ent* ents; int /*<<< orphan*/  lock; } ;
struct j1939_ecu {size_t addr; scalar_t__ nusers; struct j1939_priv* priv; } ;
struct j1939_addr_ent {int /*<<< orphan*/  nusers; int /*<<< orphan*/ * ecu; } ;

/* Variables and functions */
 int /*<<< orphan*/  j1939_address_is_unicast (size_t) ; 
 int /*<<< orphan*/  j1939_ecu_is_mapped_locked (struct j1939_ecu*) ; 
 int /*<<< orphan*/  j1939_ecu_put (struct j1939_ecu*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void j1939_ecu_unmap_locked(struct j1939_ecu *ecu)
{
	struct j1939_priv *priv = ecu->priv;
	struct j1939_addr_ent *ent;

	lockdep_assert_held(&priv->lock);

	if (!j1939_address_is_unicast(ecu->addr))
		return;

	if (!j1939_ecu_is_mapped_locked(ecu))
		return;

	ent = &priv->ents[ecu->addr];
	ent->ecu = NULL;
	ent->nusers -= ecu->nusers;
	j1939_ecu_put(ecu);
}