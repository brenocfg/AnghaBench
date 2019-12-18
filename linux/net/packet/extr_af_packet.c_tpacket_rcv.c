#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
union tpacket_uhdr {struct sockaddr_ll* raw; TYPE_5__* h3; TYPE_4__* h2; TYPE_3__* h1; } ;
struct sockaddr_ll {scalar_t__ sll_pkttype; int /*<<< orphan*/  sll_ifindex; int /*<<< orphan*/  sll_protocol; int /*<<< orphan*/  sll_hatype; int /*<<< orphan*/  sll_family; int /*<<< orphan*/  sll_addr; int /*<<< orphan*/  sll_halen; } ;
typedef  struct sockaddr_ll u8 ;
typedef  unsigned int u32 ;
struct virtio_net_hdr {int dummy; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_17__ {int /*<<< orphan*/  lock; } ;
struct sock {scalar_t__ sk_type; scalar_t__ sk_rcvbuf; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;TYPE_8__ sk_receive_queue; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {int len; scalar_t__ pkt_type; scalar_t__ ip_summed; struct sockaddr_ll* data; int /*<<< orphan*/  protocol; int /*<<< orphan*/  vlan_proto; } ;
struct packet_type {struct sock* af_packet_priv; } ;
struct TYPE_16__ {unsigned short frame_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  tp_packets; } ;
struct TYPE_12__ {TYPE_1__ stats1; } ;
struct packet_sock {unsigned short tp_hdrlen; int tp_reserve; int tp_version; int origdev; int /*<<< orphan*/  tp_drops; TYPE_6__ rx_ring; int /*<<< orphan*/  tp_tstamp; TYPE_2__ stats; scalar_t__ copy_thresh; scalar_t__ has_vnet_hdr; } ;
struct net_device {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  type; scalar_t__ header_ops; } ;
typedef  unsigned long __u32 ;
struct TYPE_18__ {unsigned short max_frame_len; } ;
struct TYPE_15__ {unsigned long tp_status; unsigned int tp_len; unsigned int tp_snaplen; unsigned short tp_mac; unsigned short tp_net; int tp_nsec; int /*<<< orphan*/  tp_padding; int /*<<< orphan*/  tp_sec; } ;
struct TYPE_14__ {unsigned int tp_len; unsigned int tp_snaplen; unsigned short tp_mac; unsigned short tp_net; int tp_nsec; int /*<<< orphan*/  tp_padding; int /*<<< orphan*/  tp_vlan_tpid; int /*<<< orphan*/  tp_vlan_tci; int /*<<< orphan*/  tp_sec; } ;
struct TYPE_13__ {unsigned int tp_len; unsigned int tp_snaplen; unsigned short tp_mac; unsigned short tp_net; int tp_usec; int /*<<< orphan*/  tp_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ CHECKSUM_COMPLETE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 TYPE_9__* GET_PBDQC_FROM_RB (TYPE_6__*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NSEC_PER_USEC ; 
 scalar_t__ PACKET_LOOPBACK ; 
 scalar_t__ PACKET_OUTGOING ; 
 scalar_t__ PAGE_ALIGN (unsigned long) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ ROOM_NONE ; 
 scalar_t__ SOCK_DGRAM ; 
 int TPACKET_ALIGN (unsigned short) ; 
#define  TPACKET_V1 130 
#define  TPACKET_V2 129 
#define  TPACKET_V3 128 
 unsigned long TP_STATUS_COPY ; 
 unsigned long TP_STATUS_CSUMNOTREADY ; 
 unsigned long TP_STATUS_CSUM_VALID ; 
 int /*<<< orphan*/  TP_STATUS_KERNEL ; 
 unsigned long TP_STATUS_LOSING ; 
 unsigned long TP_STATUS_USER ; 
 unsigned long TP_STATUS_VLAN_TPID_VALID ; 
 unsigned long TP_STATUS_VLAN_VALID ; 
 scalar_t__ __packet_rcv_has_room (struct packet_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  __packet_set_status (struct packet_sock*,struct sockaddr_ll*,unsigned long) ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_8__*,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_parse_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getnstimeofday (struct timespec*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct sockaddr_ll* packet_current_rx_frame (struct packet_sock*,struct sk_buff*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  packet_increment_rx_head (struct packet_sock*,TYPE_6__*) ; 
 int /*<<< orphan*/  pgv_to_page (struct sockaddr_ll*) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 
 int /*<<< orphan*/  pr_err_once (char*,unsigned int,unsigned int,unsigned short) ; 
 int /*<<< orphan*/  prb_clear_blk_fill_status (TYPE_6__*) ; 
 unsigned int run_filter (struct sk_buff*,struct sock*,unsigned int) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,struct sockaddr_ll*,unsigned int) ; 
 scalar_t__ skb_csum_unnecessary (struct sk_buff*) ; 
 struct sk_buff* skb_get (struct sk_buff*) ; 
 int skb_mac_header (struct sk_buff*) ; 
 unsigned int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,struct sockaddr_ll*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 unsigned long tpacket_get_timestamp (struct sk_buff*,struct timespec*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vio_le () ; 
 scalar_t__ virtio_net_hdr_from_skb (struct sk_buff*,struct sockaddr_ll*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpacket_rcv(struct sk_buff *skb, struct net_device *dev,
		       struct packet_type *pt, struct net_device *orig_dev)
{
	struct sock *sk;
	struct packet_sock *po;
	struct sockaddr_ll *sll;
	union tpacket_uhdr h;
	u8 *skb_head = skb->data;
	int skb_len = skb->len;
	unsigned int snaplen, res;
	unsigned long status = TP_STATUS_USER;
	unsigned short macoff, netoff, hdrlen;
	struct sk_buff *copy_skb = NULL;
	struct timespec ts;
	__u32 ts_status;
	bool is_drop_n_account = false;
	bool do_vnet = false;

	/* struct tpacket{2,3}_hdr is aligned to a multiple of TPACKET_ALIGNMENT.
	 * We may add members to them until current aligned size without forcing
	 * userspace to call getsockopt(..., PACKET_HDRLEN, ...).
	 */
	BUILD_BUG_ON(TPACKET_ALIGN(sizeof(*h.h2)) != 32);
	BUILD_BUG_ON(TPACKET_ALIGN(sizeof(*h.h3)) != 48);

	if (skb->pkt_type == PACKET_LOOPBACK)
		goto drop;

	sk = pt->af_packet_priv;
	po = pkt_sk(sk);

	if (!net_eq(dev_net(dev), sock_net(sk)))
		goto drop;

	if (dev->header_ops) {
		if (sk->sk_type != SOCK_DGRAM)
			skb_push(skb, skb->data - skb_mac_header(skb));
		else if (skb->pkt_type == PACKET_OUTGOING) {
			/* Special case: outgoing packets have ll header at head */
			skb_pull(skb, skb_network_offset(skb));
		}
	}

	snaplen = skb->len;

	res = run_filter(skb, sk, snaplen);
	if (!res)
		goto drop_n_restore;

	/* If we are flooded, just give up */
	if (__packet_rcv_has_room(po, skb) == ROOM_NONE) {
		atomic_inc(&po->tp_drops);
		goto drop_n_restore;
	}

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		status |= TP_STATUS_CSUMNOTREADY;
	else if (skb->pkt_type != PACKET_OUTGOING &&
		 (skb->ip_summed == CHECKSUM_COMPLETE ||
		  skb_csum_unnecessary(skb)))
		status |= TP_STATUS_CSUM_VALID;

	if (snaplen > res)
		snaplen = res;

	if (sk->sk_type == SOCK_DGRAM) {
		macoff = netoff = TPACKET_ALIGN(po->tp_hdrlen) + 16 +
				  po->tp_reserve;
	} else {
		unsigned int maclen = skb_network_offset(skb);
		netoff = TPACKET_ALIGN(po->tp_hdrlen +
				       (maclen < 16 ? 16 : maclen)) +
				       po->tp_reserve;
		if (po->has_vnet_hdr) {
			netoff += sizeof(struct virtio_net_hdr);
			do_vnet = true;
		}
		macoff = netoff - maclen;
	}
	if (po->tp_version <= TPACKET_V2) {
		if (macoff + snaplen > po->rx_ring.frame_size) {
			if (po->copy_thresh &&
			    atomic_read(&sk->sk_rmem_alloc) < sk->sk_rcvbuf) {
				if (skb_shared(skb)) {
					copy_skb = skb_clone(skb, GFP_ATOMIC);
				} else {
					copy_skb = skb_get(skb);
					skb_head = skb->data;
				}
				if (copy_skb)
					skb_set_owner_r(copy_skb, sk);
			}
			snaplen = po->rx_ring.frame_size - macoff;
			if ((int)snaplen < 0) {
				snaplen = 0;
				do_vnet = false;
			}
		}
	} else if (unlikely(macoff + snaplen >
			    GET_PBDQC_FROM_RB(&po->rx_ring)->max_frame_len)) {
		u32 nval;

		nval = GET_PBDQC_FROM_RB(&po->rx_ring)->max_frame_len - macoff;
		pr_err_once("tpacket_rcv: packet too big, clamped from %u to %u. macoff=%u\n",
			    snaplen, nval, macoff);
		snaplen = nval;
		if (unlikely((int)snaplen < 0)) {
			snaplen = 0;
			macoff = GET_PBDQC_FROM_RB(&po->rx_ring)->max_frame_len;
			do_vnet = false;
		}
	}
	spin_lock(&sk->sk_receive_queue.lock);
	h.raw = packet_current_rx_frame(po, skb,
					TP_STATUS_KERNEL, (macoff+snaplen));
	if (!h.raw)
		goto drop_n_account;
	if (po->tp_version <= TPACKET_V2) {
		packet_increment_rx_head(po, &po->rx_ring);
	/*
	 * LOSING will be reported till you read the stats,
	 * because it's COR - Clear On Read.
	 * Anyways, moving it for V1/V2 only as V3 doesn't need this
	 * at packet level.
	 */
		if (atomic_read(&po->tp_drops))
			status |= TP_STATUS_LOSING;
	}

	if (do_vnet &&
	    virtio_net_hdr_from_skb(skb, h.raw + macoff -
				    sizeof(struct virtio_net_hdr),
				    vio_le(), true, 0))
		goto drop_n_account;

	po->stats.stats1.tp_packets++;
	if (copy_skb) {
		status |= TP_STATUS_COPY;
		__skb_queue_tail(&sk->sk_receive_queue, copy_skb);
	}
	spin_unlock(&sk->sk_receive_queue.lock);

	skb_copy_bits(skb, 0, h.raw + macoff, snaplen);

	if (!(ts_status = tpacket_get_timestamp(skb, &ts, po->tp_tstamp)))
		getnstimeofday(&ts);

	status |= ts_status;

	switch (po->tp_version) {
	case TPACKET_V1:
		h.h1->tp_len = skb->len;
		h.h1->tp_snaplen = snaplen;
		h.h1->tp_mac = macoff;
		h.h1->tp_net = netoff;
		h.h1->tp_sec = ts.tv_sec;
		h.h1->tp_usec = ts.tv_nsec / NSEC_PER_USEC;
		hdrlen = sizeof(*h.h1);
		break;
	case TPACKET_V2:
		h.h2->tp_len = skb->len;
		h.h2->tp_snaplen = snaplen;
		h.h2->tp_mac = macoff;
		h.h2->tp_net = netoff;
		h.h2->tp_sec = ts.tv_sec;
		h.h2->tp_nsec = ts.tv_nsec;
		if (skb_vlan_tag_present(skb)) {
			h.h2->tp_vlan_tci = skb_vlan_tag_get(skb);
			h.h2->tp_vlan_tpid = ntohs(skb->vlan_proto);
			status |= TP_STATUS_VLAN_VALID | TP_STATUS_VLAN_TPID_VALID;
		} else {
			h.h2->tp_vlan_tci = 0;
			h.h2->tp_vlan_tpid = 0;
		}
		memset(h.h2->tp_padding, 0, sizeof(h.h2->tp_padding));
		hdrlen = sizeof(*h.h2);
		break;
	case TPACKET_V3:
		/* tp_nxt_offset,vlan are already populated above.
		 * So DONT clear those fields here
		 */
		h.h3->tp_status |= status;
		h.h3->tp_len = skb->len;
		h.h3->tp_snaplen = snaplen;
		h.h3->tp_mac = macoff;
		h.h3->tp_net = netoff;
		h.h3->tp_sec  = ts.tv_sec;
		h.h3->tp_nsec = ts.tv_nsec;
		memset(h.h3->tp_padding, 0, sizeof(h.h3->tp_padding));
		hdrlen = sizeof(*h.h3);
		break;
	default:
		BUG();
	}

	sll = h.raw + TPACKET_ALIGN(hdrlen);
	sll->sll_halen = dev_parse_header(skb, sll->sll_addr);
	sll->sll_family = AF_PACKET;
	sll->sll_hatype = dev->type;
	sll->sll_protocol = skb->protocol;
	sll->sll_pkttype = skb->pkt_type;
	if (unlikely(po->origdev))
		sll->sll_ifindex = orig_dev->ifindex;
	else
		sll->sll_ifindex = dev->ifindex;

	smp_mb();

#if ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE == 1
	if (po->tp_version <= TPACKET_V2) {
		u8 *start, *end;

		end = (u8 *) PAGE_ALIGN((unsigned long) h.raw +
					macoff + snaplen);

		for (start = h.raw; start < end; start += PAGE_SIZE)
			flush_dcache_page(pgv_to_page(start));
	}
	smp_wmb();
#endif

	if (po->tp_version <= TPACKET_V2) {
		__packet_set_status(po, h.raw, status);
		sk->sk_data_ready(sk);
	} else {
		prb_clear_blk_fill_status(&po->rx_ring);
	}

drop_n_restore:
	if (skb_head != skb->data && skb_shared(skb)) {
		skb->data = skb_head;
		skb->len = skb_len;
	}
drop:
	if (!is_drop_n_account)
		consume_skb(skb);
	else
		kfree_skb(skb);
	return 0;

drop_n_account:
	spin_unlock(&sk->sk_receive_queue.lock);
	atomic_inc(&po->tp_drops);
	is_drop_n_account = true;

	sk->sk_data_ready(sk);
	kfree_skb(copy_skb);
	goto drop_n_restore;
}