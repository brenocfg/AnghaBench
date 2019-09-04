#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {unsigned char* data; int /*<<< orphan*/  len; } ;
struct ipv6hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_MAXPLEN ; 
#define  IPV6_TLV_JUMBO 130 
#define  IPV6_TLV_PAD1 129 
#define  IPV6_TLV_PADN 128 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_trim_rcsum (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_headlen (struct sk_buff*) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static int br_nf_check_hbh_len(struct sk_buff *skb)
{
	unsigned char *raw = (u8 *)(ipv6_hdr(skb) + 1);
	u32 pkt_len;
	const unsigned char *nh = skb_network_header(skb);
	int off = raw - nh;
	int len = (raw[1] + 1) << 3;

	if ((raw + len) - skb->data > skb_headlen(skb))
		goto bad;

	off += 2;
	len -= 2;

	while (len > 0) {
		int optlen = nh[off + 1] + 2;

		switch (nh[off]) {
		case IPV6_TLV_PAD1:
			optlen = 1;
			break;

		case IPV6_TLV_PADN:
			break;

		case IPV6_TLV_JUMBO:
			if (nh[off + 1] != 4 || (off & 3) != 2)
				goto bad;
			pkt_len = ntohl(*(__be32 *)(nh + off + 2));
			if (pkt_len <= IPV6_MAXPLEN ||
			    ipv6_hdr(skb)->payload_len)
				goto bad;
			if (pkt_len > skb->len - sizeof(struct ipv6hdr))
				goto bad;
			if (pskb_trim_rcsum(skb,
					    pkt_len + sizeof(struct ipv6hdr)))
				goto bad;
			nh = skb_network_header(skb);
			break;
		default:
			if (optlen > len)
				goto bad;
			break;
		}
		off += optlen;
		len -= optlen;
	}
	if (len == 0)
		return 0;
bad:
	return -1;
}