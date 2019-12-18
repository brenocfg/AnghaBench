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
struct ethhdr {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int EBADR ; 
 int ENODATA ; 
 int EREMOTE ; 
 int /*<<< orphan*/  batadv_is_my_mac (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int batadv_check_unicast_packet(struct batadv_priv *bat_priv,
				       struct sk_buff *skb, int hdr_size)
{
	struct ethhdr *ethhdr;

	/* drop packet if it has not necessary minimum size */
	if (unlikely(!pskb_may_pull(skb, hdr_size)))
		return -ENODATA;

	ethhdr = eth_hdr(skb);

	/* packet with unicast indication but non-unicast recipient */
	if (!is_valid_ether_addr(ethhdr->h_dest))
		return -EBADR;

	/* packet with broadcast/multicast sender address */
	if (is_multicast_ether_addr(ethhdr->h_source))
		return -EBADR;

	/* not for me */
	if (!batadv_is_my_mac(bat_priv, ethhdr->h_dest))
		return -EREMOTE;

	return 0;
}