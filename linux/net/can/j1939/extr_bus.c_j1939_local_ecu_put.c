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
typedef  size_t u8 ;
struct j1939_priv {int /*<<< orphan*/  lock; TYPE_1__* ents; } ;
struct j1939_ecu {size_t addr; int /*<<< orphan*/  nusers; } ;
typedef  int /*<<< orphan*/  name_t ;
struct TYPE_2__ {int /*<<< orphan*/  nusers; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ j1939_address_is_unicast (size_t) ; 
 struct j1939_ecu* j1939_ecu_find_by_name_locked (struct j1939_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ j1939_ecu_is_mapped_locked (struct j1939_ecu*) ; 
 int /*<<< orphan*/  j1939_ecu_put (struct j1939_ecu*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void j1939_local_ecu_put(struct j1939_priv *priv, name_t name, u8 sa)
{
	struct j1939_ecu *ecu;

	write_lock_bh(&priv->lock);

	if (j1939_address_is_unicast(sa))
		priv->ents[sa].nusers--;

	if (!name)
		goto done;

	ecu = j1939_ecu_find_by_name_locked(priv, name);
	if (WARN_ON_ONCE(!ecu))
		goto done;

	ecu->nusers--;
	/* TODO: do we care if ecu->addr != sa? */
	if (j1939_ecu_is_mapped_locked(ecu))
		/* ecu's sa is active already */
		priv->ents[ecu->addr].nusers--;
	j1939_ecu_put(ecu);

 done:
	write_unlock_bh(&priv->lock);
}