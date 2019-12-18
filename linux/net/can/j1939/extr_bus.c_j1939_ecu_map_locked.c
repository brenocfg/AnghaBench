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
struct j1939_priv {int /*<<< orphan*/  ndev; struct j1939_addr_ent* ents; int /*<<< orphan*/  lock; } ;
struct j1939_ecu {size_t addr; scalar_t__ nusers; int /*<<< orphan*/  name; struct j1939_priv* priv; } ;
struct j1939_addr_ent {int /*<<< orphan*/  nusers; struct j1939_ecu* ecu; } ;

/* Variables and functions */
 int /*<<< orphan*/  j1939_address_is_unicast (size_t) ; 
 int /*<<< orphan*/  j1939_ecu_get (struct j1939_ecu*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void j1939_ecu_map_locked(struct j1939_ecu *ecu)
{
	struct j1939_priv *priv = ecu->priv;
	struct j1939_addr_ent *ent;

	lockdep_assert_held(&priv->lock);

	if (!j1939_address_is_unicast(ecu->addr))
		return;

	ent = &priv->ents[ecu->addr];

	if (ent->ecu) {
		netdev_warn(priv->ndev, "Trying to map already mapped ECU, addr: 0x%02x, name: 0x%016llx. Skip it.\n",
			    ecu->addr, ecu->name);
		return;
	}

	j1939_ecu_get(ecu);
	ent->ecu = ecu;
	ent->nusers += ecu->nusers;
}