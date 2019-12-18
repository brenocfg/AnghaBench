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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct sk_buff {scalar_t__ ip_summed; size_t csum_offset; scalar_t__ encapsulation; scalar_t__ data; int /*<<< orphan*/  dev; } ;
struct ip_tunnel_encap {int flags; scalar_t__ sport; } ;
struct guehdr {size_t hlen; int /*<<< orphan*/  flags; int /*<<< orphan*/  proto_ctype; scalar_t__ version; scalar_t__ control; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int EINVAL ; 
 int /*<<< orphan*/  GUE_FLAG_PRIV ; 
 size_t GUE_LEN_PRIV ; 
 int /*<<< orphan*/  GUE_PFLAG_REMCSUM ; 
 scalar_t__ GUE_PLEN_REMCSUM ; 
 int SKB_GSO_TUNNEL_REMCSUM ; 
 int TUNNEL_ENCAP_FLAG_REMCSUM ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (size_t) ; 
 int iptunnel_handle_offloads (struct sk_buff*,int) ; 
 size_t skb_checksum_start_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  udp_flow_src_port (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int __gue_build_header(struct sk_buff *skb, struct ip_tunnel_encap *e,
		       u8 *protocol, __be16 *sport, int type)
{
	struct guehdr *guehdr;
	size_t hdrlen, optlen = 0;
	void *data;
	bool need_priv = false;
	int err;

	if ((e->flags & TUNNEL_ENCAP_FLAG_REMCSUM) &&
	    skb->ip_summed == CHECKSUM_PARTIAL) {
		optlen += GUE_PLEN_REMCSUM;
		type |= SKB_GSO_TUNNEL_REMCSUM;
		need_priv = true;
	}

	optlen += need_priv ? GUE_LEN_PRIV : 0;

	err = iptunnel_handle_offloads(skb, type);
	if (err)
		return err;

	/* Get source port (based on flow hash) before skb_push */
	*sport = e->sport ? : udp_flow_src_port(dev_net(skb->dev),
						skb, 0, 0, false);

	hdrlen = sizeof(struct guehdr) + optlen;

	skb_push(skb, hdrlen);

	guehdr = (struct guehdr *)skb->data;

	guehdr->control = 0;
	guehdr->version = 0;
	guehdr->hlen = optlen >> 2;
	guehdr->flags = 0;
	guehdr->proto_ctype = *protocol;

	data = &guehdr[1];

	if (need_priv) {
		__be32 *flags = data;

		guehdr->flags |= GUE_FLAG_PRIV;
		*flags = 0;
		data += GUE_LEN_PRIV;

		if (type & SKB_GSO_TUNNEL_REMCSUM) {
			u16 csum_start = skb_checksum_start_offset(skb);
			__be16 *pd = data;

			if (csum_start < hdrlen)
				return -EINVAL;

			csum_start -= hdrlen;
			pd[0] = htons(csum_start);
			pd[1] = htons(csum_start + skb->csum_offset);

			if (!skb_is_gso(skb)) {
				skb->ip_summed = CHECKSUM_NONE;
				skb->encapsulation = 0;
			}

			*flags |= GUE_PFLAG_REMCSUM;
			data += GUE_PLEN_REMCSUM;
		}

	}

	return 0;
}