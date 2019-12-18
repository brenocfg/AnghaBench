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
struct sk_buff {int dummy; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_UNICAST_4ADDR ; 
 int batadv_send_skb_via_tt_generic (struct batadv_priv*,struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned short) ; 

__attribute__((used)) static inline int batadv_send_skb_via_tt_4addr(struct batadv_priv *bat_priv,
					       struct sk_buff *skb,
					       int packet_subtype,
					       u8 *dst_hint,
					       unsigned short vid)
{
	return batadv_send_skb_via_tt_generic(bat_priv, skb,
					      BATADV_UNICAST_4ADDR,
					      packet_subtype, dst_hint, vid);
}