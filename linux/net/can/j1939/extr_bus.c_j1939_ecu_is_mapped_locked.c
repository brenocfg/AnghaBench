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
struct j1939_priv {int /*<<< orphan*/  lock; } ;
struct j1939_ecu {int /*<<< orphan*/  addr; struct j1939_priv* priv; } ;

/* Variables and functions */
 struct j1939_ecu* j1939_ecu_find_by_addr_locked (struct j1939_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool j1939_ecu_is_mapped_locked(struct j1939_ecu *ecu)
{
	struct j1939_priv *priv = ecu->priv;

	lockdep_assert_held(&priv->lock);

	return j1939_ecu_find_by_addr_locked(priv, ecu->addr) == ecu;
}