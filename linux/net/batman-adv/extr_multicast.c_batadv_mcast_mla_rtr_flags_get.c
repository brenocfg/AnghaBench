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
struct net_device {int dummy; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int BATADV_MCAST_WANT_NO_RTR4 ; 
 int BATADV_MCAST_WANT_NO_RTR6 ; 
 int batadv_mcast_mla_rtr_flags_bridge_get (struct batadv_priv*,struct net_device*) ; 
 int batadv_mcast_mla_rtr_flags_softif_get (struct batadv_priv*,struct net_device*) ; 

__attribute__((used)) static u8 batadv_mcast_mla_rtr_flags_get(struct batadv_priv *bat_priv,
					 struct net_device *bridge)
{
	u8 flags = BATADV_MCAST_WANT_NO_RTR4 | BATADV_MCAST_WANT_NO_RTR6;

	flags &= batadv_mcast_mla_rtr_flags_softif_get(bat_priv, bridge);
	flags &= batadv_mcast_mla_rtr_flags_bridge_get(bat_priv, bridge);

	return flags;
}