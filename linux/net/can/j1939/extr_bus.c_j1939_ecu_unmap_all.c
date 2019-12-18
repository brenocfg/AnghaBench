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
struct j1939_priv {int /*<<< orphan*/  lock; TYPE_1__* ents; } ;
struct TYPE_2__ {scalar_t__ ecu; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  j1939_ecu_unmap_locked (scalar_t__) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void j1939_ecu_unmap_all(struct j1939_priv *priv)
{
	int i;

	write_lock_bh(&priv->lock);
	for (i = 0; i < ARRAY_SIZE(priv->ents); i++)
		if (priv->ents[i].ecu)
			j1939_ecu_unmap_locked(priv->ents[i].ecu);
	write_unlock_bh(&priv->lock);
}