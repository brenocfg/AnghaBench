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
typedef  int /*<<< orphan*/  u8 ;
struct batadv_tvlv_handler {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  handler_list_lock; } ;
struct batadv_priv {TYPE_1__ tvlv; } ;

/* Variables and functions */
 struct batadv_tvlv_handler* batadv_tvlv_handler_get (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tvlv_handler_put (struct batadv_tvlv_handler*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void batadv_tvlv_handler_unregister(struct batadv_priv *bat_priv,
				    u8 type, u8 version)
{
	struct batadv_tvlv_handler *tvlv_handler;

	tvlv_handler = batadv_tvlv_handler_get(bat_priv, type, version);
	if (!tvlv_handler)
		return;

	batadv_tvlv_handler_put(tvlv_handler);
	spin_lock_bh(&bat_priv->tvlv.handler_list_lock);
	hlist_del_rcu(&tvlv_handler->list);
	spin_unlock_bh(&bat_priv->tvlv.handler_list_lock);
	batadv_tvlv_handler_put(tvlv_handler);
}