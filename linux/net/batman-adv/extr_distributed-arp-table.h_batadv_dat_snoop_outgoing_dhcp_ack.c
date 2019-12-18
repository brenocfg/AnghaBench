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
struct sk_buff {int dummy; } ;
struct batadv_priv {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */

__attribute__((used)) static inline void
batadv_dat_snoop_outgoing_dhcp_ack(struct batadv_priv *bat_priv,
				   struct sk_buff *skb, __be16 proto,
				   unsigned short vid)
{
}