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
struct j1939_priv {TYPE_1__* ents; int /*<<< orphan*/  lock; } ;
struct j1939_ecu {int dummy; } ;
struct TYPE_2__ {struct j1939_ecu* ecu; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

struct j1939_ecu *j1939_ecu_find_by_addr_locked(struct j1939_priv *priv,
						u8 addr)
{
	lockdep_assert_held(&priv->lock);

	return priv->ents[addr].ecu;
}