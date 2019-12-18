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

/* Variables and functions */

__attribute__((used)) static inline bool
batadv_dat_snoop_outgoing_arp_request(struct batadv_priv *bat_priv,
				      struct sk_buff *skb)
{
	return false;
}