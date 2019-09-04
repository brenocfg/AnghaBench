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
struct batadv_tvlv_container {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  container_list_lock; } ;
struct batadv_priv {TYPE_1__ tvlv; } ;

/* Variables and functions */
 struct batadv_tvlv_container* batadv_tvlv_container_get (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tvlv_container_remove (struct batadv_priv*,struct batadv_tvlv_container*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void batadv_tvlv_container_unregister(struct batadv_priv *bat_priv,
				      u8 type, u8 version)
{
	struct batadv_tvlv_container *tvlv;

	spin_lock_bh(&bat_priv->tvlv.container_list_lock);
	tvlv = batadv_tvlv_container_get(bat_priv, type, version);
	batadv_tvlv_container_remove(bat_priv, tvlv);
	spin_unlock_bh(&bat_priv->tvlv.container_list_lock);
}