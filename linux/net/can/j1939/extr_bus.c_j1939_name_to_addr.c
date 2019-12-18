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
typedef  int u8 ;
struct j1939_priv {int /*<<< orphan*/  lock; } ;
struct j1939_ecu {int addr; } ;
typedef  int /*<<< orphan*/  name_t ;

/* Variables and functions */
 int J1939_IDLE_ADDR ; 
 int J1939_NO_ADDR ; 
 struct j1939_ecu* j1939_ecu_find_by_name_locked (struct j1939_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ j1939_ecu_is_mapped_locked (struct j1939_ecu*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

u8 j1939_name_to_addr(struct j1939_priv *priv, name_t name)
{
	struct j1939_ecu *ecu;
	int addr = J1939_IDLE_ADDR;

	if (!name)
		return J1939_NO_ADDR;

	read_lock_bh(&priv->lock);
	ecu = j1939_ecu_find_by_name_locked(priv, name);
	if (ecu && j1939_ecu_is_mapped_locked(ecu))
		/* ecu's SA is registered */
		addr = ecu->addr;

	read_unlock_bh(&priv->lock);

	return addr;
}