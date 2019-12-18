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
typedef  int u8 ;
typedef  int u16 ;
struct udphdr {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int /*<<< orphan*/  version; } ;
struct guehdr {int version; int hlen; int flags; int proto_ctype; int /*<<< orphan*/  control; } ;
struct fou {scalar_t__ family; int flags; } ;
typedef  int __be32 ;
struct TYPE_4__ {void* tot_len; } ;
struct TYPE_3__ {void* payload_len; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int FOU_F_REMCSUM_NOPARTIAL ; 
 int GUE_FLAG_PRIV ; 
 int GUE_LEN_PRIV ; 
 int GUE_PFLAG_REMCSUM ; 
 int GUE_PLEN_REMCSUM ; 
 int IPPROTO_IPIP ; 
 int IPPROTO_IPV6 ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 struct fou* fou_from_sock (struct sock*) ; 
 int /*<<< orphan*/  fou_recv_pull (struct sk_buff*,struct fou*,int) ; 
 int gue_control_message (struct sk_buff*,struct guehdr*) ; 
 struct guehdr* gue_remcsum (struct sk_buff*,struct guehdr*,void*,size_t,int,int) ; 
 void* htons (scalar_t__) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ iptunnel_pull_offloads (struct sk_buff*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ ntohs (void*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/ * udp_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ validate_gue_flags (struct guehdr*,size_t) ; 

__attribute__((used)) static int gue_udp_recv(struct sock *sk, struct sk_buff *skb)
{
	struct fou *fou = fou_from_sock(sk);
	size_t len, optlen, hdrlen;
	struct guehdr *guehdr;
	void *data;
	u16 doffset = 0;
	u8 proto_ctype;

	if (!fou)
		return 1;

	len = sizeof(struct udphdr) + sizeof(struct guehdr);
	if (!pskb_may_pull(skb, len))
		goto drop;

	guehdr = (struct guehdr *)&udp_hdr(skb)[1];

	switch (guehdr->version) {
	case 0: /* Full GUE header present */
		break;

	case 1: {
		/* Direct encapsulation of IPv4 or IPv6 */

		int prot;

		switch (((struct iphdr *)guehdr)->version) {
		case 4:
			prot = IPPROTO_IPIP;
			break;
		case 6:
			prot = IPPROTO_IPV6;
			break;
		default:
			goto drop;
		}

		if (fou_recv_pull(skb, fou, sizeof(struct udphdr)))
			goto drop;

		return -prot;
	}

	default: /* Undefined version */
		goto drop;
	}

	optlen = guehdr->hlen << 2;
	len += optlen;

	if (!pskb_may_pull(skb, len))
		goto drop;

	/* guehdr may change after pull */
	guehdr = (struct guehdr *)&udp_hdr(skb)[1];

	if (validate_gue_flags(guehdr, optlen))
		goto drop;

	hdrlen = sizeof(struct guehdr) + optlen;

	if (fou->family == AF_INET)
		ip_hdr(skb)->tot_len = htons(ntohs(ip_hdr(skb)->tot_len) - len);
	else
		ipv6_hdr(skb)->payload_len =
		    htons(ntohs(ipv6_hdr(skb)->payload_len) - len);

	/* Pull csum through the guehdr now . This can be used if
	 * there is a remote checksum offload.
	 */
	skb_postpull_rcsum(skb, udp_hdr(skb), len);

	data = &guehdr[1];

	if (guehdr->flags & GUE_FLAG_PRIV) {
		__be32 flags = *(__be32 *)(data + doffset);

		doffset += GUE_LEN_PRIV;

		if (flags & GUE_PFLAG_REMCSUM) {
			guehdr = gue_remcsum(skb, guehdr, data + doffset,
					     hdrlen, guehdr->proto_ctype,
					     !!(fou->flags &
						FOU_F_REMCSUM_NOPARTIAL));
			if (!guehdr)
				goto drop;

			data = &guehdr[1];

			doffset += GUE_PLEN_REMCSUM;
		}
	}

	if (unlikely(guehdr->control))
		return gue_control_message(skb, guehdr);

	proto_ctype = guehdr->proto_ctype;
	__skb_pull(skb, sizeof(struct udphdr) + hdrlen);
	skb_reset_transport_header(skb);

	if (iptunnel_pull_offloads(skb))
		goto drop;

	return -proto_ctype;

drop:
	kfree_skb(skb);
	return 0;
}