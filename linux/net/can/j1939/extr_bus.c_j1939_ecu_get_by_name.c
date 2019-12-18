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
struct j1939_ecu {int dummy; } ;
typedef  int /*<<< orphan*/  name_t ;

/* Variables and functions */
 struct j1939_ecu* j1939_ecu_get_by_name_locked (struct j1939_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

struct j1939_ecu *j1939_ecu_get_by_name(struct j1939_priv *priv, name_t name)
{
	struct j1939_ecu *ecu;

	read_lock_bh(&priv->lock);
	ecu = j1939_ecu_get_by_name_locked(priv, name);
	read_unlock_bh(&priv->lock);

	return ecu;
}