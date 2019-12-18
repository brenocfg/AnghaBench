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
struct sk_buff {unsigned int len; } ;
struct ipv6hdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tot_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 int pskb_trim_rcsum (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int tcf_ct_skb_network_trim(struct sk_buff *skb, int family)
{
	unsigned int len;
	int err;

	switch (family) {
	case NFPROTO_IPV4:
		len = ntohs(ip_hdr(skb)->tot_len);
		break;
	case NFPROTO_IPV6:
		len = sizeof(struct ipv6hdr)
			+ ntohs(ipv6_hdr(skb)->payload_len);
		break;
	default:
		len = skb->len;
	}

	err = pskb_trim_rcsum(skb, len);

	return err;
}