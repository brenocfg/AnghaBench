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
typedef  int /*<<< orphan*/  u16 ;
struct udphdr {scalar_t__ check; void* len; void* dest; void* source; } ;
struct sk_buff {scalar_t__ csum; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  pkt_type; struct net_device* dev; void* protocol; int /*<<< orphan*/  priority; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct pktgen_hdr {int dummy; } ;
struct pktgen_dev {int nr_labels; int vlan_id; int svlan_id; int cur_pkt_size; int pkt_overhead; int cur_udp_src; int cur_udp_dst; int ip_id; int flags; int /*<<< orphan*/  cur_daddr; int /*<<< orphan*/  cur_saddr; int /*<<< orphan*/  tos; int /*<<< orphan*/  hh; int /*<<< orphan*/  skb_priority; int /*<<< orphan*/  vlan_p; int /*<<< orphan*/  vlan_cfi; int /*<<< orphan*/  svlan_p; int /*<<< orphan*/  svlan_cfi; int /*<<< orphan*/  result; int /*<<< orphan*/  cur_queue_map; } ;
struct net_device {int features; } ;
struct iphdr {int ihl; int version; int ttl; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; void* tot_len; scalar_t__ frag_off; void* id; int /*<<< orphan*/  protocol; int /*<<< orphan*/  tos; } ;
typedef  int /*<<< orphan*/  __wsum ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  void* __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_PARTIAL ; 
 scalar_t__ CSUM_MANGLED_0 ; 
 int ETH_P_8021Q ; 
 int ETH_P_IP ; 
 int ETH_P_MPLS_UC ; 
 int F_UDPCSUM ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 void* build_tci (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_cur_headers (struct pktgen_dev*) ; 
 int /*<<< orphan*/  mpls_push (int /*<<< orphan*/ *,struct pktgen_dev*) ; 
 struct sk_buff* pktgen_alloc_skb (struct net_device*,struct pktgen_dev*) ; 
 int /*<<< orphan*/  pktgen_finalize_skb (struct pktgen_dev*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_ipsec (struct pktgen_dev*,struct sk_buff*,void*) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_push (struct sk_buff*,int) ; 
 void* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udp4_hwcsum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *fill_packet_ipv4(struct net_device *odev,
					struct pktgen_dev *pkt_dev)
{
	struct sk_buff *skb = NULL;
	__u8 *eth;
	struct udphdr *udph;
	int datalen, iplen;
	struct iphdr *iph;
	__be16 protocol = htons(ETH_P_IP);
	__be32 *mpls;
	__be16 *vlan_tci = NULL;                 /* Encapsulates priority and VLAN ID */
	__be16 *vlan_encapsulated_proto = NULL;  /* packet type ID field (or len) for VLAN tag */
	__be16 *svlan_tci = NULL;                /* Encapsulates priority and SVLAN ID */
	__be16 *svlan_encapsulated_proto = NULL; /* packet type ID field (or len) for SVLAN tag */
	u16 queue_map;

	if (pkt_dev->nr_labels)
		protocol = htons(ETH_P_MPLS_UC);

	if (pkt_dev->vlan_id != 0xffff)
		protocol = htons(ETH_P_8021Q);

	/* Update any of the values, used when we're incrementing various
	 * fields.
	 */
	mod_cur_headers(pkt_dev);
	queue_map = pkt_dev->cur_queue_map;

	skb = pktgen_alloc_skb(odev, pkt_dev);
	if (!skb) {
		sprintf(pkt_dev->result, "No memory");
		return NULL;
	}

	prefetchw(skb->data);
	skb_reserve(skb, 16);

	/*  Reserve for ethernet and IP header  */
	eth = skb_push(skb, 14);
	mpls = skb_put(skb, pkt_dev->nr_labels * sizeof(__u32));
	if (pkt_dev->nr_labels)
		mpls_push(mpls, pkt_dev);

	if (pkt_dev->vlan_id != 0xffff) {
		if (pkt_dev->svlan_id != 0xffff) {
			svlan_tci = skb_put(skb, sizeof(__be16));
			*svlan_tci = build_tci(pkt_dev->svlan_id,
					       pkt_dev->svlan_cfi,
					       pkt_dev->svlan_p);
			svlan_encapsulated_proto = skb_put(skb,
							   sizeof(__be16));
			*svlan_encapsulated_proto = htons(ETH_P_8021Q);
		}
		vlan_tci = skb_put(skb, sizeof(__be16));
		*vlan_tci = build_tci(pkt_dev->vlan_id,
				      pkt_dev->vlan_cfi,
				      pkt_dev->vlan_p);
		vlan_encapsulated_proto = skb_put(skb, sizeof(__be16));
		*vlan_encapsulated_proto = htons(ETH_P_IP);
	}

	skb_reset_mac_header(skb);
	skb_set_network_header(skb, skb->len);
	iph = skb_put(skb, sizeof(struct iphdr));

	skb_set_transport_header(skb, skb->len);
	udph = skb_put(skb, sizeof(struct udphdr));
	skb_set_queue_mapping(skb, queue_map);
	skb->priority = pkt_dev->skb_priority;

	memcpy(eth, pkt_dev->hh, 12);
	*(__be16 *) & eth[12] = protocol;

	/* Eth + IPh + UDPh + mpls */
	datalen = pkt_dev->cur_pkt_size - 14 - 20 - 8 -
		  pkt_dev->pkt_overhead;
	if (datalen < 0 || datalen < sizeof(struct pktgen_hdr))
		datalen = sizeof(struct pktgen_hdr);

	udph->source = htons(pkt_dev->cur_udp_src);
	udph->dest = htons(pkt_dev->cur_udp_dst);
	udph->len = htons(datalen + 8);	/* DATA + udphdr */
	udph->check = 0;

	iph->ihl = 5;
	iph->version = 4;
	iph->ttl = 32;
	iph->tos = pkt_dev->tos;
	iph->protocol = IPPROTO_UDP;	/* UDP */
	iph->saddr = pkt_dev->cur_saddr;
	iph->daddr = pkt_dev->cur_daddr;
	iph->id = htons(pkt_dev->ip_id);
	pkt_dev->ip_id++;
	iph->frag_off = 0;
	iplen = 20 + 8 + datalen;
	iph->tot_len = htons(iplen);
	ip_send_check(iph);
	skb->protocol = protocol;
	skb->dev = odev;
	skb->pkt_type = PACKET_HOST;

	pktgen_finalize_skb(pkt_dev, skb, datalen);

	if (!(pkt_dev->flags & F_UDPCSUM)) {
		skb->ip_summed = CHECKSUM_NONE;
	} else if (odev->features & (NETIF_F_HW_CSUM | NETIF_F_IP_CSUM)) {
		skb->ip_summed = CHECKSUM_PARTIAL;
		skb->csum = 0;
		udp4_hwcsum(skb, iph->saddr, iph->daddr);
	} else {
		__wsum csum = skb_checksum(skb, skb_transport_offset(skb), datalen + 8, 0);

		/* add protocol-dependent pseudo-header */
		udph->check = csum_tcpudp_magic(iph->saddr, iph->daddr,
						datalen + 8, IPPROTO_UDP, csum);

		if (udph->check == 0)
			udph->check = CSUM_MANGLED_0;
	}

#ifdef CONFIG_XFRM
	if (!process_ipsec(pkt_dev, skb, protocol))
		return NULL;
#endif

	return skb;
}