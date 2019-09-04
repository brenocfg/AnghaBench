#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vxlanhdr {int vx_flags; int vx_vni; } ;
struct vxlan_sock {int flags; } ;
struct vxlan_metadata {int dummy; } ;
struct vxlan_dev {int /*<<< orphan*/  gro_cells; TYPE_3__* dev; int /*<<< orphan*/  net; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  pkt_type; TYPE_3__* dev; } ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_5__ {int /*<<< orphan*/  tun_info; } ;
struct metadata_dst {TYPE_1__ u; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_6__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  tstats; int /*<<< orphan*/  rx_dropped; TYPE_2__ stats; int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TEB ; 
 int IFF_UP ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  TUNNEL_KEY ; 
 int VXLAN_F_GBP ; 
 int VXLAN_F_GPE ; 
 int VXLAN_F_REMCSUM_RX ; 
 int VXLAN_HF_VNI ; 
 int /*<<< orphan*/  VXLAN_HLEN ; 
 int VXLAN_VNI_MASK ; 
 scalar_t__ __iptunnel_pull_header (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (TYPE_3__*) ; 
 int /*<<< orphan*/  gro_cells_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct vxlan_metadata* ip_tunnel_info_opts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key32_to_tunnel_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct vxlan_metadata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct vxlan_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 void* skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 struct metadata_dst* udp_tun_rx_dst (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vxlan_collect_metadata (struct vxlan_sock*) ; 
 int /*<<< orphan*/  vxlan_ecn_decapsulate (struct vxlan_sock*,void*,struct sk_buff*) ; 
 int /*<<< orphan*/  vxlan_get_sk_family (struct vxlan_sock*) ; 
 struct vxlanhdr* vxlan_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  vxlan_parse_gbp_hdr (struct vxlanhdr*,struct sk_buff*,int,struct vxlan_metadata*) ; 
 int /*<<< orphan*/  vxlan_parse_gpe_hdr (struct vxlanhdr*,int /*<<< orphan*/ *,struct sk_buff*,int) ; 
 int /*<<< orphan*/  vxlan_remcsum (struct vxlanhdr*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  vxlan_set_mac (struct vxlan_dev*,struct vxlan_sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_vni (int) ; 
 struct vxlan_dev* vxlan_vs_find_vni (struct vxlan_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxlan_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct pcpu_sw_netstats *stats;
	struct vxlan_dev *vxlan;
	struct vxlan_sock *vs;
	struct vxlanhdr unparsed;
	struct vxlan_metadata _md;
	struct vxlan_metadata *md = &_md;
	__be16 protocol = htons(ETH_P_TEB);
	bool raw_proto = false;
	void *oiph;
	__be32 vni = 0;

	/* Need UDP and VXLAN header to be present */
	if (!pskb_may_pull(skb, VXLAN_HLEN))
		goto drop;

	unparsed = *vxlan_hdr(skb);
	/* VNI flag always required to be set */
	if (!(unparsed.vx_flags & VXLAN_HF_VNI)) {
		netdev_dbg(skb->dev, "invalid vxlan flags=%#x vni=%#x\n",
			   ntohl(vxlan_hdr(skb)->vx_flags),
			   ntohl(vxlan_hdr(skb)->vx_vni));
		/* Return non vxlan pkt */
		goto drop;
	}
	unparsed.vx_flags &= ~VXLAN_HF_VNI;
	unparsed.vx_vni &= ~VXLAN_VNI_MASK;

	vs = rcu_dereference_sk_user_data(sk);
	if (!vs)
		goto drop;

	vni = vxlan_vni(vxlan_hdr(skb)->vx_vni);

	vxlan = vxlan_vs_find_vni(vs, skb->dev->ifindex, vni);
	if (!vxlan)
		goto drop;

	/* For backwards compatibility, only allow reserved fields to be
	 * used by VXLAN extensions if explicitly requested.
	 */
	if (vs->flags & VXLAN_F_GPE) {
		if (!vxlan_parse_gpe_hdr(&unparsed, &protocol, skb, vs->flags))
			goto drop;
		raw_proto = true;
	}

	if (__iptunnel_pull_header(skb, VXLAN_HLEN, protocol, raw_proto,
				   !net_eq(vxlan->net, dev_net(vxlan->dev))))
			goto drop;

	if (vxlan_collect_metadata(vs)) {
		struct metadata_dst *tun_dst;

		tun_dst = udp_tun_rx_dst(skb, vxlan_get_sk_family(vs), TUNNEL_KEY,
					 key32_to_tunnel_id(vni), sizeof(*md));

		if (!tun_dst)
			goto drop;

		md = ip_tunnel_info_opts(&tun_dst->u.tun_info);

		skb_dst_set(skb, (struct dst_entry *)tun_dst);
	} else {
		memset(md, 0, sizeof(*md));
	}

	if (vs->flags & VXLAN_F_REMCSUM_RX)
		if (!vxlan_remcsum(&unparsed, skb, vs->flags))
			goto drop;
	if (vs->flags & VXLAN_F_GBP)
		vxlan_parse_gbp_hdr(&unparsed, skb, vs->flags, md);
	/* Note that GBP and GPE can never be active together. This is
	 * ensured in vxlan_dev_configure.
	 */

	if (unparsed.vx_flags || unparsed.vx_vni) {
		/* If there are any unprocessed flags remaining treat
		 * this as a malformed packet. This behavior diverges from
		 * VXLAN RFC (RFC7348) which stipulates that bits in reserved
		 * in reserved fields are to be ignored. The approach here
		 * maintains compatibility with previous stack code, and also
		 * is more robust and provides a little more security in
		 * adding extensions to VXLAN.
		 */
		goto drop;
	}

	if (!raw_proto) {
		if (!vxlan_set_mac(vxlan, vs, skb, vni))
			goto drop;
	} else {
		skb_reset_mac_header(skb);
		skb->dev = vxlan->dev;
		skb->pkt_type = PACKET_HOST;
	}

	oiph = skb_network_header(skb);
	skb_reset_network_header(skb);

	if (!vxlan_ecn_decapsulate(vs, oiph, skb)) {
		++vxlan->dev->stats.rx_frame_errors;
		++vxlan->dev->stats.rx_errors;
		goto drop;
	}

	rcu_read_lock();

	if (unlikely(!(vxlan->dev->flags & IFF_UP))) {
		rcu_read_unlock();
		atomic_long_inc(&vxlan->dev->rx_dropped);
		goto drop;
	}

	stats = this_cpu_ptr(vxlan->dev->tstats);
	u64_stats_update_begin(&stats->syncp);
	stats->rx_packets++;
	stats->rx_bytes += skb->len;
	u64_stats_update_end(&stats->syncp);

	gro_cells_receive(&vxlan->gro_cells, skb);

	rcu_read_unlock();

	return 0;

drop:
	/* Consume bad packet */
	kfree_skb(skb);
	return 0;
}