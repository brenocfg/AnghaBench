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
struct sock {scalar_t__ sk_family; } ;
struct sk_buff {scalar_t__ dev; scalar_t__ ipvs_property; } ;
struct netns_ipvs {TYPE_1__* net; int /*<<< orphan*/  conn_out_counter; int /*<<< orphan*/  enable; } ;
struct ip_vs_protocol {scalar_t__ protocol; int /*<<< orphan*/  conn_out_get; int /*<<< orphan*/  dont_defrag; } ;
struct ip_vs_proto_data {struct ip_vs_protocol* pp; } ;
struct ip_vs_iphdr {scalar_t__ protocol; int /*<<< orphan*/  off; int /*<<< orphan*/  len; int /*<<< orphan*/  saddr; } ;
struct ip_vs_conn {int dummy; } ;
typedef  int /*<<< orphan*/  _ports ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {scalar_t__ nodefrag; } ;
struct TYPE_3__ {scalar_t__ loopback_dev; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  EnterFunction (int) ; 
 int /*<<< orphan*/  ICMPV6_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMPV6_PORT_UNREACH ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_PORT_UNREACH ; 
 struct ip_vs_conn* INDIRECT_CALL_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netns_ipvs*,int,struct sk_buff*,struct ip_vs_iphdr*) ; 
 scalar_t__ IPPROTO_ICMP ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 scalar_t__ IPPROTO_SCTP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ IP_VS_CONN_F_MASQ ; 
 int /*<<< orphan*/  IP_VS_DBG_PKT (int,int,struct ip_vs_protocol*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ IP_VS_FWD_METHOD (struct ip_vs_conn*) ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 unsigned int NF_INET_LOCAL_OUT ; 
 unsigned int NF_STOLEN ; 
 scalar_t__ PF_INET ; 
 int /*<<< orphan*/  __ip_vs_conn_put (struct ip_vs_conn*) ; 
 struct ip_vs_conn* __ip_vs_rs_conn_out (unsigned int,struct netns_ipvs*,int,struct sk_buff*,struct ip_vs_iphdr*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frag_safe_skb_hp (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 unsigned int handle_response (int,struct sk_buff*,struct ip_vs_proto_data*,struct ip_vs_conn*,struct ip_vs_iphdr*,unsigned int) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_is_fragment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_conn_out_get_proto ; 
 int /*<<< orphan*/  ip_vs_defrag_user (unsigned int) ; 
 int /*<<< orphan*/  ip_vs_fill_iph_skb (int,struct sk_buff*,int,struct ip_vs_iphdr*) ; 
 scalar_t__ ip_vs_gather_frags (struct netns_ipvs*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ ip_vs_has_real_service (struct netns_ipvs*,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ip_vs_out_icmp (struct netns_ipvs*,struct sk_buff*,int*,unsigned int) ; 
 int ip_vs_out_icmp_v6 (struct netns_ipvs*,struct sk_buff*,int*,unsigned int,struct ip_vs_iphdr*) ; 
 struct ip_vs_proto_data* ip_vs_proto_data_get (struct netns_ipvs*,scalar_t__) ; 
 int /*<<< orphan*/  is_sctp_abort (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_tcp_reset (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 struct sock* skb_to_full_sk (struct sk_buff*) ; 
 scalar_t__ sysctl_nat_icmp_send (struct netns_ipvs*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int
ip_vs_out(struct netns_ipvs *ipvs, unsigned int hooknum, struct sk_buff *skb, int af)
{
	struct ip_vs_iphdr iph;
	struct ip_vs_protocol *pp;
	struct ip_vs_proto_data *pd;
	struct ip_vs_conn *cp;
	struct sock *sk;

	EnterFunction(11);

	/* Already marked as IPVS request or reply? */
	if (skb->ipvs_property)
		return NF_ACCEPT;

	sk = skb_to_full_sk(skb);
	/* Bad... Do not break raw sockets */
	if (unlikely(sk && hooknum == NF_INET_LOCAL_OUT &&
		     af == AF_INET)) {

		if (sk->sk_family == PF_INET && inet_sk(sk)->nodefrag)
			return NF_ACCEPT;
	}

	if (unlikely(!skb_dst(skb)))
		return NF_ACCEPT;

	if (!ipvs->enable)
		return NF_ACCEPT;

	ip_vs_fill_iph_skb(af, skb, false, &iph);
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6) {
		if (unlikely(iph.protocol == IPPROTO_ICMPV6)) {
			int related;
			int verdict = ip_vs_out_icmp_v6(ipvs, skb, &related,
							hooknum, &iph);

			if (related)
				return verdict;
		}
	} else
#endif
		if (unlikely(iph.protocol == IPPROTO_ICMP)) {
			int related;
			int verdict = ip_vs_out_icmp(ipvs, skb, &related, hooknum);

			if (related)
				return verdict;
		}

	pd = ip_vs_proto_data_get(ipvs, iph.protocol);
	if (unlikely(!pd))
		return NF_ACCEPT;
	pp = pd->pp;

	/* reassemble IP fragments */
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET)
#endif
		if (unlikely(ip_is_fragment(ip_hdr(skb)) && !pp->dont_defrag)) {
			if (ip_vs_gather_frags(ipvs, skb,
					       ip_vs_defrag_user(hooknum)))
				return NF_STOLEN;

			ip_vs_fill_iph_skb(AF_INET, skb, false, &iph);
		}

	/*
	 * Check if the packet belongs to an existing entry
	 */
	cp = INDIRECT_CALL_1(pp->conn_out_get, ip_vs_conn_out_get_proto,
			     ipvs, af, skb, &iph);

	if (likely(cp)) {
		if (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ)
			goto ignore_cp;
		return handle_response(af, skb, pd, cp, &iph, hooknum);
	}

	/* Check for real-server-started requests */
	if (atomic_read(&ipvs->conn_out_counter)) {
		/* Currently only for UDP:
		 * connection oriented protocols typically use
		 * ephemeral ports for outgoing connections, so
		 * related incoming responses would not match any VS
		 */
		if (pp->protocol == IPPROTO_UDP) {
			cp = __ip_vs_rs_conn_out(hooknum, ipvs, af, skb, &iph);
			if (likely(cp))
				return handle_response(af, skb, pd, cp, &iph,
						       hooknum);
		}
	}

	if (sysctl_nat_icmp_send(ipvs) &&
	    (pp->protocol == IPPROTO_TCP ||
	     pp->protocol == IPPROTO_UDP ||
	     pp->protocol == IPPROTO_SCTP)) {
		__be16 _ports[2], *pptr;

		pptr = frag_safe_skb_hp(skb, iph.len,
					 sizeof(_ports), _ports);
		if (pptr == NULL)
			return NF_ACCEPT;	/* Not for me */
		if (ip_vs_has_real_service(ipvs, af, iph.protocol, &iph.saddr,
					   pptr[0])) {
			/*
			 * Notify the real server: there is no
			 * existing entry if it is not RST
			 * packet or not TCP packet.
			 */
			if ((iph.protocol != IPPROTO_TCP &&
			     iph.protocol != IPPROTO_SCTP)
			     || ((iph.protocol == IPPROTO_TCP
				  && !is_tcp_reset(skb, iph.len))
				 || (iph.protocol == IPPROTO_SCTP
					&& !is_sctp_abort(skb,
						iph.len)))) {
#ifdef CONFIG_IP_VS_IPV6
				if (af == AF_INET6) {
					if (!skb->dev)
						skb->dev = ipvs->net->loopback_dev;
					icmpv6_send(skb,
						    ICMPV6_DEST_UNREACH,
						    ICMPV6_PORT_UNREACH,
						    0);
				} else
#endif
					icmp_send(skb,
						  ICMP_DEST_UNREACH,
						  ICMP_PORT_UNREACH, 0);
				return NF_DROP;
			}
		}
	}

out:
	IP_VS_DBG_PKT(12, af, pp, skb, iph.off,
		      "ip_vs_out: packet continues traversal as normal");
	return NF_ACCEPT;

ignore_cp:
	__ip_vs_conn_put(cp);
	goto out;
}