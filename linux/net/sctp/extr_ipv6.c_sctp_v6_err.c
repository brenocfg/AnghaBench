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
struct sock {int sk_err; int sk_err_soft; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;} ;
struct sk_buff {void* transport_header; void* network_header; int /*<<< orphan*/  dev; } ;
struct sctp_transport {int dummy; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;
struct ipv6_pinfo {scalar_t__ recverr; } ;
struct inet6_skb_parm {int dummy; } ;
struct inet6_dev {int dummy; } ;
typedef  void* __u16 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int ENOENT ; 
 int /*<<< orphan*/  ICMP6_MIB_INERRORS ; 
#define  ICMPV6_PARAMPROB 130 
#define  ICMPV6_PKT_TOOBIG 129 
 int ICMPV6_UNK_NEXTHDR ; 
#define  NDISC_REDIRECT 128 
 int /*<<< orphan*/  __ICMP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmpv6_err_convert (int,int,int*) ; 
 struct inet6_dev* in6_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_sk_accept_pmtu (struct sock*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_err_finish (struct sock*,struct sctp_transport*) ; 
 struct sock* sctp_err_lookup (struct net*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,struct sctp_association**,struct sctp_transport**) ; 
 int /*<<< orphan*/  sctp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_icmp_frag_needed (struct sock*,struct sctp_association*,struct sctp_transport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_icmp_proto_unreachable (struct sock*,struct sctp_association*,struct sctp_transport*) ; 
 int /*<<< orphan*/  sctp_icmp_redirect (struct sock*,struct sctp_transport*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int sctp_v6_err(struct sk_buff *skb, struct inet6_skb_parm *opt,
			u8 type, u8 code, int offset, __be32 info)
{
	struct inet6_dev *idev;
	struct sock *sk;
	struct sctp_association *asoc;
	struct sctp_transport *transport;
	struct ipv6_pinfo *np;
	__u16 saveip, savesctp;
	int err, ret = 0;
	struct net *net = dev_net(skb->dev);

	idev = in6_dev_get(skb->dev);

	/* Fix up skb to look at the embedded net header. */
	saveip	 = skb->network_header;
	savesctp = skb->transport_header;
	skb_reset_network_header(skb);
	skb_set_transport_header(skb, offset);
	sk = sctp_err_lookup(net, AF_INET6, skb, sctp_hdr(skb), &asoc, &transport);
	/* Put back, the original pointers. */
	skb->network_header   = saveip;
	skb->transport_header = savesctp;
	if (!sk) {
		__ICMP6_INC_STATS(net, idev, ICMP6_MIB_INERRORS);
		ret = -ENOENT;
		goto out;
	}

	/* Warning:  The sock lock is held.  Remember to call
	 * sctp_err_finish!
	 */

	switch (type) {
	case ICMPV6_PKT_TOOBIG:
		if (ip6_sk_accept_pmtu(sk))
			sctp_icmp_frag_needed(sk, asoc, transport, ntohl(info));
		goto out_unlock;
	case ICMPV6_PARAMPROB:
		if (ICMPV6_UNK_NEXTHDR == code) {
			sctp_icmp_proto_unreachable(sk, asoc, transport);
			goto out_unlock;
		}
		break;
	case NDISC_REDIRECT:
		sctp_icmp_redirect(sk, transport, skb);
		goto out_unlock;
	default:
		break;
	}

	np = inet6_sk(sk);
	icmpv6_err_convert(type, code, &err);
	if (!sock_owned_by_user(sk) && np->recverr) {
		sk->sk_err = err;
		sk->sk_error_report(sk);
	} else {  /* Only an error on timeout */
		sk->sk_err_soft = err;
	}

out_unlock:
	sctp_err_finish(sk, transport);
out:
	if (likely(idev != NULL))
		in6_dev_put(idev);

	return ret;
}