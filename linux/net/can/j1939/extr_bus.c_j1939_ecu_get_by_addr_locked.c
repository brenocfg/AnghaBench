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
typedef  int /*<<< orphan*/  u8 ;
struct j1939_priv {int /*<<< orphan*/  lock; } ;
struct j1939_ecu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  j1939_address_is_unicast (int /*<<< orphan*/ ) ; 
 struct j1939_ecu* j1939_ecu_find_by_addr_locked (struct j1939_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_ecu_get (struct j1939_ecu*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

struct j1939_ecu *j1939_ecu_get_by_addr_locked(struct j1939_priv *priv, u8 addr)
{
	struct j1939_ecu *ecu;

	lockdep_assert_held(&priv->lock);

	if (!j1939_address_is_unicast(addr))
		return NULL;

	ecu = j1939_ecu_find_by_addr_locked(priv, addr);
	if (ecu)
		j1939_ecu_get(ecu);

	return ecu;
}