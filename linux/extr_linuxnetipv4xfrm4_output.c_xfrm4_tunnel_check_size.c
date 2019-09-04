#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int protocol; scalar_t__ sk; scalar_t__ ignore_df; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int frag_off; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_FRAG_NEEDED ; 
 TYPE_2__* IPCB (struct sk_buff*) ; 
 int IPSKB_XFRM_TUNNEL_SIZE ; 
 int /*<<< orphan*/  IP_DF ; 
 int dst_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_skb_dst_mtu (scalar_t__,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_gso_validate_network_len (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm_local_error (struct sk_buff*,int) ; 

__attribute__((used)) static int xfrm4_tunnel_check_size(struct sk_buff *skb)
{
	int mtu, ret = 0;

	if (IPCB(skb)->flags & IPSKB_XFRM_TUNNEL_SIZE)
		goto out;

	if (!(ip_hdr(skb)->frag_off & htons(IP_DF)) || skb->ignore_df)
		goto out;

	mtu = dst_mtu(skb_dst(skb));
	if ((!skb_is_gso(skb) && skb->len > mtu) ||
	    (skb_is_gso(skb) &&
	     !skb_gso_validate_network_len(skb, ip_skb_dst_mtu(skb->sk, skb)))) {
		skb->protocol = htons(ETH_P_IP);

		if (skb->sk)
			xfrm_local_error(skb, mtu);
		else
			icmp_send(skb, ICMP_DEST_UNREACH,
				  ICMP_FRAG_NEEDED, htonl(mtu));
		ret = -EMSGSIZE;
	}
out:
	return ret;
}