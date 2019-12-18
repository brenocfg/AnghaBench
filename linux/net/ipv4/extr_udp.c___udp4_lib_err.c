#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct udphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct udp_table {int dummy; } ;
struct sock {scalar_t__ sk_state; int sk_err; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;} ;
struct sk_buff {TYPE_3__* dev; scalar_t__ data; } ;
struct net {int dummy; } ;
struct iphdr {int ihl; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct inet_sock {int /*<<< orphan*/  recverr; int /*<<< orphan*/  pmtudisc; } ;
struct TYPE_6__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_5__ {int fatal; int errno; } ;
struct TYPE_4__ {int type; int code; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  ENOENT ; 
 int EPROTO ; 
 struct sock* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  ICMP_DEST_UNREACH 132 
 int const ICMP_FRAG_NEEDED ; 
 int /*<<< orphan*/  ICMP_MIB_INERRORS ; 
#define  ICMP_PARAMETERPROB 131 
#define  ICMP_REDIRECT 130 
#define  ICMP_SOURCE_QUENCH 129 
#define  ICMP_TIME_EXCEEDED 128 
 int /*<<< orphan*/  IP_PMTUDISC_DONT ; 
 scalar_t__ IS_ERR (struct sock*) ; 
 int const NR_ICMP_UNREACH ; 
 int PTR_ERR (struct sock*) ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  __ICMP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 struct sock* __udp4_lib_err_encap (struct net*,struct iphdr const*,struct udphdr*,struct udp_table*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sock* __udp4_lib_lookup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct udp_table*,int /*<<< orphan*/ *) ; 
 struct net* dev_net (TYPE_3__*) ; 
 TYPE_2__* icmp_err_convert ; 
 TYPE_1__* icmp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  inet_sdif (struct sk_buff*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip_icmp_error (struct sock*,struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv4_sk_redirect (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  ipv4_sk_update_pmtu (struct sk_buff*,struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  udp_encap_needed_key ; 

int __udp4_lib_err(struct sk_buff *skb, u32 info, struct udp_table *udptable)
{
	struct inet_sock *inet;
	const struct iphdr *iph = (const struct iphdr *)skb->data;
	struct udphdr *uh = (struct udphdr *)(skb->data+(iph->ihl<<2));
	const int type = icmp_hdr(skb)->type;
	const int code = icmp_hdr(skb)->code;
	bool tunnel = false;
	struct sock *sk;
	int harderr;
	int err;
	struct net *net = dev_net(skb->dev);

	sk = __udp4_lib_lookup(net, iph->daddr, uh->dest,
			       iph->saddr, uh->source, skb->dev->ifindex,
			       inet_sdif(skb), udptable, NULL);
	if (!sk) {
		/* No socket for error: try tunnels before discarding */
		sk = ERR_PTR(-ENOENT);
		if (static_branch_unlikely(&udp_encap_needed_key)) {
			sk = __udp4_lib_err_encap(net, iph, uh, udptable, skb,
						  info);
			if (!sk)
				return 0;
		}

		if (IS_ERR(sk)) {
			__ICMP_INC_STATS(net, ICMP_MIB_INERRORS);
			return PTR_ERR(sk);
		}

		tunnel = true;
	}

	err = 0;
	harderr = 0;
	inet = inet_sk(sk);

	switch (type) {
	default:
	case ICMP_TIME_EXCEEDED:
		err = EHOSTUNREACH;
		break;
	case ICMP_SOURCE_QUENCH:
		goto out;
	case ICMP_PARAMETERPROB:
		err = EPROTO;
		harderr = 1;
		break;
	case ICMP_DEST_UNREACH:
		if (code == ICMP_FRAG_NEEDED) { /* Path MTU discovery */
			ipv4_sk_update_pmtu(skb, sk, info);
			if (inet->pmtudisc != IP_PMTUDISC_DONT) {
				err = EMSGSIZE;
				harderr = 1;
				break;
			}
			goto out;
		}
		err = EHOSTUNREACH;
		if (code <= NR_ICMP_UNREACH) {
			harderr = icmp_err_convert[code].fatal;
			err = icmp_err_convert[code].errno;
		}
		break;
	case ICMP_REDIRECT:
		ipv4_sk_redirect(skb, sk);
		goto out;
	}

	/*
	 *      RFC1122: OK.  Passes ICMP errors back to application, as per
	 *	4.1.3.3.
	 */
	if (tunnel) {
		/* ...not for tunnels though: we don't have a sending socket */
		goto out;
	}
	if (!inet->recverr) {
		if (!harderr || sk->sk_state != TCP_ESTABLISHED)
			goto out;
	} else
		ip_icmp_error(sk, skb, err, uh->dest, info, (u8 *)(uh+1));

	sk->sk_err = err;
	sk->sk_error_report(sk);
out:
	return 0;
}