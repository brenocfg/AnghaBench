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
typedef  int u_int8_t ;
typedef  int u_int16_t ;
typedef  int u8 ;
typedef  int u16 ;
struct xt_tcpmss_info {scalar_t__ mss; } ;
struct xt_action_param {scalar_t__ fragoff; struct xt_tcpmss_info* targinfo; } ;
struct tcphdr {int doff; int /*<<< orphan*/  check; } ;
struct sk_buff {unsigned int len; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NFPROTO_IPV4 ; 
 int TCPOLEN_MSS ; 
 int TCPOPT_MSS ; 
 scalar_t__ XT_TCPMSS_CLAMP_PMTU ; 
 int dst_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  inet_proto_csum_replace2 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inet_proto_csum_replace4 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 void* min (int,int) ; 
 int /*<<< orphan*/  net_err_ratelimited (char*,unsigned int) ; 
 scalar_t__ optlen (int*,unsigned int) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 
 unsigned int tcpmss_reverse_mtu (struct net*,struct sk_buff*,unsigned int) ; 
 scalar_t__ xt_family (struct xt_action_param const*) ; 
 struct net* xt_net (struct xt_action_param const*) ; 

__attribute__((used)) static int
tcpmss_mangle_packet(struct sk_buff *skb,
		     const struct xt_action_param *par,
		     unsigned int family,
		     unsigned int tcphoff,
		     unsigned int minlen)
{
	const struct xt_tcpmss_info *info = par->targinfo;
	struct tcphdr *tcph;
	int len, tcp_hdrlen;
	unsigned int i;
	__be16 oldval;
	u16 newmss;
	u8 *opt;

	/* This is a fragment, no TCP header is available */
	if (par->fragoff != 0)
		return 0;

	if (skb_ensure_writable(skb, skb->len))
		return -1;

	len = skb->len - tcphoff;
	if (len < (int)sizeof(struct tcphdr))
		return -1;

	tcph = (struct tcphdr *)(skb_network_header(skb) + tcphoff);
	tcp_hdrlen = tcph->doff * 4;

	if (len < tcp_hdrlen || tcp_hdrlen < sizeof(struct tcphdr))
		return -1;

	if (info->mss == XT_TCPMSS_CLAMP_PMTU) {
		struct net *net = xt_net(par);
		unsigned int in_mtu = tcpmss_reverse_mtu(net, skb, family);
		unsigned int min_mtu = min(dst_mtu(skb_dst(skb)), in_mtu);

		if (min_mtu <= minlen) {
			net_err_ratelimited("unknown or invalid path-MTU (%u)\n",
					    min_mtu);
			return -1;
		}
		newmss = min_mtu - minlen;
	} else
		newmss = info->mss;

	opt = (u_int8_t *)tcph;
	for (i = sizeof(struct tcphdr); i <= tcp_hdrlen - TCPOLEN_MSS; i += optlen(opt, i)) {
		if (opt[i] == TCPOPT_MSS && opt[i+1] == TCPOLEN_MSS) {
			u_int16_t oldmss;

			oldmss = (opt[i+2] << 8) | opt[i+3];

			/* Never increase MSS, even when setting it, as
			 * doing so results in problems for hosts that rely
			 * on MSS being set correctly.
			 */
			if (oldmss <= newmss)
				return 0;

			opt[i+2] = (newmss & 0xff00) >> 8;
			opt[i+3] = newmss & 0x00ff;

			inet_proto_csum_replace2(&tcph->check, skb,
						 htons(oldmss), htons(newmss),
						 false);
			return 0;
		}
	}

	/* There is data after the header so the option can't be added
	 * without moving it, and doing so may make the SYN packet
	 * itself too large. Accept the packet unmodified instead.
	 */
	if (len > tcp_hdrlen)
		return 0;

	/* tcph->doff has 4 bits, do not wrap it to 0 */
	if (tcp_hdrlen >= 15 * 4)
		return 0;

	/*
	 * MSS Option not found ?! add it..
	 */
	if (skb_tailroom(skb) < TCPOLEN_MSS) {
		if (pskb_expand_head(skb, 0,
				     TCPOLEN_MSS - skb_tailroom(skb),
				     GFP_ATOMIC))
			return -1;
		tcph = (struct tcphdr *)(skb_network_header(skb) + tcphoff);
	}

	skb_put(skb, TCPOLEN_MSS);

	/*
	 * IPv4: RFC 1122 states "If an MSS option is not received at
	 * connection setup, TCP MUST assume a default send MSS of 536".
	 * IPv6: RFC 2460 states IPv6 has a minimum MTU of 1280 and a minimum
	 * length IPv6 header of 60, ergo the default MSS value is 1220
	 * Since no MSS was provided, we must use the default values
	 */
	if (xt_family(par) == NFPROTO_IPV4)
		newmss = min(newmss, (u16)536);
	else
		newmss = min(newmss, (u16)1220);

	opt = (u_int8_t *)tcph + sizeof(struct tcphdr);
	memmove(opt + TCPOLEN_MSS, opt, len - sizeof(struct tcphdr));

	inet_proto_csum_replace2(&tcph->check, skb,
				 htons(len), htons(len + TCPOLEN_MSS), true);
	opt[0] = TCPOPT_MSS;
	opt[1] = TCPOLEN_MSS;
	opt[2] = (newmss & 0xff00) >> 8;
	opt[3] = newmss & 0x00ff;

	inet_proto_csum_replace4(&tcph->check, skb, 0, *((__be32 *)opt), false);

	oldval = ((__be16 *)tcph)[6];
	tcph->doff += TCPOLEN_MSS/4;
	inet_proto_csum_replace2(&tcph->check, skb,
				 oldval, ((__be16 *)tcph)[6], false);
	return TCPOLEN_MSS;
}