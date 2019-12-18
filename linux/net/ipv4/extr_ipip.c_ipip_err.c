#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {TYPE_4__* dev; scalar_t__ data; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  protocol; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct ip_tunnel_net {int dummy; } ;
struct TYPE_5__ {scalar_t__ daddr; scalar_t__ ttl; } ;
struct TYPE_6__ {TYPE_1__ iph; int /*<<< orphan*/  link; } ;
struct ip_tunnel {int err_count; scalar_t__ err_time; TYPE_2__ parms; } ;
struct TYPE_8__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_7__ {int type; int code; } ;

/* Variables and functions */
 int ENOENT ; 
#define  ICMP_DEST_UNREACH 131 
 int const ICMP_EXC_TTL ; 
 int const ICMP_FRAG_NEEDED ; 
#define  ICMP_REDIRECT 130 
#define  ICMP_SR_FAILED 129 
#define  ICMP_TIME_EXCEEDED 128 
 scalar_t__ IPTUNNEL_ERR_TIMEO ; 
 int /*<<< orphan*/  TUNNEL_NO_KEY ; 
 struct net* dev_net (TYPE_4__*) ; 
 TYPE_3__* icmp_hdr (struct sk_buff*) ; 
 struct ip_tunnel* ip_tunnel_lookup (struct ip_tunnel_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipip_net_id ; 
 int /*<<< orphan*/  ipv4_redirect (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_update_pmtu (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct ip_tunnel_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ipip_err(struct sk_buff *skb, u32 info)
{
	/* All the routers (except for Linux) return only
	 * 8 bytes of packet payload. It means, that precise relaying of
	 * ICMP in the real Internet is absolutely infeasible.
	 */
	struct net *net = dev_net(skb->dev);
	struct ip_tunnel_net *itn = net_generic(net, ipip_net_id);
	const struct iphdr *iph = (const struct iphdr *)skb->data;
	const int type = icmp_hdr(skb)->type;
	const int code = icmp_hdr(skb)->code;
	struct ip_tunnel *t;
	int err = 0;

	t = ip_tunnel_lookup(itn, skb->dev->ifindex, TUNNEL_NO_KEY,
			     iph->daddr, iph->saddr, 0);
	if (!t) {
		err = -ENOENT;
		goto out;
	}

	switch (type) {
	case ICMP_DEST_UNREACH:
		switch (code) {
		case ICMP_SR_FAILED:
			/* Impossible event. */
			goto out;
		default:
			/* All others are translated to HOST_UNREACH.
			 * rfc2003 contains "deep thoughts" about NET_UNREACH,
			 * I believe they are just ether pollution. --ANK
			 */
			break;
		}
		break;

	case ICMP_TIME_EXCEEDED:
		if (code != ICMP_EXC_TTL)
			goto out;
		break;

	case ICMP_REDIRECT:
		break;

	default:
		goto out;
	}

	if (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED) {
		ipv4_update_pmtu(skb, net, info, t->parms.link, iph->protocol);
		goto out;
	}

	if (type == ICMP_REDIRECT) {
		ipv4_redirect(skb, net, t->parms.link, iph->protocol);
		goto out;
	}

	if (t->parms.iph.daddr == 0) {
		err = -ENOENT;
		goto out;
	}

	if (t->parms.iph.ttl == 0 && type == ICMP_TIME_EXCEEDED)
		goto out;

	if (time_before(jiffies, t->err_time + IPTUNNEL_ERR_TIMEO))
		t->err_count++;
	else
		t->err_count = 1;
	t->err_time = jiffies;

out:
	return err;
}