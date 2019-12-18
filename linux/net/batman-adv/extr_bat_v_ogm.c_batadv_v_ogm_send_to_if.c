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
struct sk_buff {scalar_t__ len; } ;
struct batadv_priv {int dummy; } ;
struct batadv_hard_iface {scalar_t__ if_status; int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CNT_MGMT_TX ; 
 int /*<<< orphan*/  BATADV_CNT_MGMT_TX_BYTES ; 
 scalar_t__ BATADV_IF_ACTIVE ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  batadv_add_counter (struct batadv_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_send_broadcast_skb (struct sk_buff*,struct batadv_hard_iface*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_v_ogm_send_to_if(struct sk_buff *skb,
				    struct batadv_hard_iface *hard_iface)
{
	struct batadv_priv *bat_priv = netdev_priv(hard_iface->soft_iface);

	if (hard_iface->if_status != BATADV_IF_ACTIVE)
		return;

	batadv_inc_counter(bat_priv, BATADV_CNT_MGMT_TX);
	batadv_add_counter(bat_priv, BATADV_CNT_MGMT_TX_BYTES,
			   skb->len + ETH_HLEN);

	batadv_send_broadcast_skb(skb, hard_iface);
}