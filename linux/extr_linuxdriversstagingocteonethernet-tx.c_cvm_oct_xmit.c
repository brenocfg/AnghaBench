#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ duplex; } ;
union cvmx_gmxx_prtx_cfg {TYPE_5__ s; int /*<<< orphan*/  u64; } ;
struct TYPE_14__ {int size; void* addr; scalar_t__ pool; } ;
union cvmx_buf_ptr {TYPE_2__ s; scalar_t__ u64; } ;
typedef  void* u64 ;
typedef  int u32 ;
struct TYPE_13__ {int /*<<< orphan*/  p; } ;
struct skb_frag_struct {int size; scalar_t__ page_offset; TYPE_1__ page; } ;
struct sk_buff {int len; scalar_t__ protocol; struct sk_buff* next; scalar_t__ data; } ;
struct octeon_ethernet {TYPE_8__* tx_free_list; scalar_t__ queue; int /*<<< orphan*/  port; scalar_t__ fau; } ;
struct TYPE_16__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {scalar_t__ tx_queue_len; TYPE_4__ stats; int /*<<< orphan*/  name; } ;
struct TYPE_15__ {int n2; int segs; int total_bytes; int subone0; int dontfree; int gather; scalar_t__ reg0; scalar_t__ ipoffp1; int /*<<< orphan*/  size0; } ;
struct TYPE_18__ {TYPE_3__ s; scalar_t__ u64; } ;
typedef  TYPE_6__ cvmx_pko_command_word0_t ;
struct TYPE_21__ {int version; int ihl; scalar_t__ frag_off; scalar_t__ protocol; } ;
struct TYPE_20__ {int /*<<< orphan*/  lock; } ;
struct TYPE_19__ {int nr_frags; struct skb_frag_struct* frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CVMX_FAU_OP_SIZE_32 ; 
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int /*<<< orphan*/  CVMX_PKO_LOCK_NONE ; 
 int CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 ; 
 int CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 ; 
 scalar_t__ CVMX_SCR_SCRATCH ; 
 int /*<<< orphan*/  CVMX_SYNCIOBDMA ; 
 scalar_t__* CVM_OCT_SKB_CB (struct sk_buff*) ; 
 int ETH_P_IP ; 
 scalar_t__ FAU_NUM_PACKET_BUFFERS_TO_FREE ; 
 scalar_t__ FAU_TOTAL_TX_TO_CLEAN ; 
 int GET_SKBUFF_QOS (struct sk_buff*) ; 
 int INDEX (int /*<<< orphan*/ ) ; 
 int INTERFACE (int /*<<< orphan*/ ) ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ MAX_OUT_QUEUE_DEPTH ; 
 int MAX_SKB_TO_FREE ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ USE_ASYNC_IOBDMA ; 
 void* XKPHYS_TO_PHYS (void*) ; 
 struct sk_buff* __skb_dequeue (TYPE_8__*) ; 
 int __skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_8__*,struct sk_buff*) ; 
 int cvm_oct_adjust_skb_to_free (int,scalar_t__) ; 
 int /*<<< orphan*/  cvm_oct_kick_tx_poll_watchdog () ; 
 int /*<<< orphan*/  cvm_oct_tx_cleanup_tasklet ; 
 int /*<<< orphan*/  cvmx_fau_async_fetch_and_add32 (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  cvmx_fau_atomic_add32 (scalar_t__,int) ; 
 int cvmx_fau_fetch_and_add32 (scalar_t__,int) ; 
 int cvmx_pko_get_num_queues (int /*<<< orphan*/ ) ; 
 int cvmx_pko_send_packet_finish (int /*<<< orphan*/ ,scalar_t__,TYPE_6__,union cvmx_buf_ptr,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pko_send_packet_prepare (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 void* cvmx_scratch_read64 (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_scratch_write64 (scalar_t__,void*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ htons (int) ; 
 TYPE_9__* ip_hdr (struct sk_buff*) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (struct octeon_ethernet*) ; 
 int /*<<< orphan*/  printk_ratelimited (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_end_pointer (struct sk_buff*) ; 
 int skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 scalar_t__ skb_queue_len (TYPE_8__*) ; 
 TYPE_7__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int cvm_oct_xmit(struct sk_buff *skb, struct net_device *dev)
{
	cvmx_pko_command_word0_t pko_command;
	union cvmx_buf_ptr hw_buffer;
	u64 old_scratch;
	u64 old_scratch2;
	int qos;
	int i;
	enum {QUEUE_CORE, QUEUE_HW, QUEUE_DROP} queue_type;
	struct octeon_ethernet *priv = netdev_priv(dev);
	struct sk_buff *to_free_list;
	int skb_to_free;
	int buffers_to_free;
	u32 total_to_clean;
	unsigned long flags;
#if REUSE_SKBUFFS_WITHOUT_FREE
	unsigned char *fpa_head;
#endif

	/*
	 * Prefetch the private data structure.  It is larger than the
	 * one cache line.
	 */
	prefetch(priv);

	/*
	 * The check on CVMX_PKO_QUEUES_PER_PORT_* is designed to
	 * completely remove "qos" in the event neither interface
	 * supports multiple queues per port.
	 */
	if ((CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 > 1) ||
	    (CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 > 1)) {
		qos = GET_SKBUFF_QOS(skb);
		if (qos <= 0)
			qos = 0;
		else if (qos >= cvmx_pko_get_num_queues(priv->port))
			qos = 0;
	} else {
		qos = 0;
	}

	if (USE_ASYNC_IOBDMA) {
		/* Save scratch in case userspace is using it */
		CVMX_SYNCIOBDMA;
		old_scratch = cvmx_scratch_read64(CVMX_SCR_SCRATCH);
		old_scratch2 = cvmx_scratch_read64(CVMX_SCR_SCRATCH + 8);

		/*
		 * Fetch and increment the number of packets to be
		 * freed.
		 */
		cvmx_fau_async_fetch_and_add32(CVMX_SCR_SCRATCH + 8,
					       FAU_NUM_PACKET_BUFFERS_TO_FREE,
					       0);
		cvmx_fau_async_fetch_and_add32(CVMX_SCR_SCRATCH,
					       priv->fau + qos * 4,
					       MAX_SKB_TO_FREE);
	}

	/*
	 * We have space for 6 segment pointers, If there will be more
	 * than that, we must linearize.
	 */
	if (unlikely(skb_shinfo(skb)->nr_frags > 5)) {
		if (unlikely(__skb_linearize(skb))) {
			queue_type = QUEUE_DROP;
			if (USE_ASYNC_IOBDMA) {
				/*
				 * Get the number of skbuffs in use
				 * by the hardware
				 */
				CVMX_SYNCIOBDMA;
				skb_to_free =
					cvmx_scratch_read64(CVMX_SCR_SCRATCH);
			} else {
				/*
				 * Get the number of skbuffs in use
				 * by the hardware
				 */
				skb_to_free = cvmx_fau_fetch_and_add32(
					priv->fau + qos * 4, MAX_SKB_TO_FREE);
			}
			skb_to_free = cvm_oct_adjust_skb_to_free(skb_to_free,
								 priv->fau +
								 qos * 4);
			spin_lock_irqsave(&priv->tx_free_list[qos].lock, flags);
			goto skip_xmit;
		}
	}

	/*
	 * The CN3XXX series of parts has an errata (GMX-401) which
	 * causes the GMX block to hang if a collision occurs towards
	 * the end of a <68 byte packet. As a workaround for this, we
	 * pad packets to be 68 bytes whenever we are in half duplex
	 * mode. We don't handle the case of having a small packet but
	 * no room to add the padding.  The kernel should always give
	 * us at least a cache line
	 */
	if ((skb->len < 64) && OCTEON_IS_MODEL(OCTEON_CN3XXX)) {
		union cvmx_gmxx_prtx_cfg gmx_prt_cfg;
		int interface = INTERFACE(priv->port);
		int index = INDEX(priv->port);

		if (interface < 2) {
			/* We only need to pad packet in half duplex mode */
			gmx_prt_cfg.u64 =
			    cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
			if (gmx_prt_cfg.s.duplex == 0) {
				int add_bytes = 64 - skb->len;

				if ((skb_tail_pointer(skb) + add_bytes) <=
				    skb_end_pointer(skb))
					__skb_put_zero(skb, add_bytes);
			}
		}
	}

	/* Build the PKO command */
	pko_command.u64 = 0;
#ifdef __LITTLE_ENDIAN
	pko_command.s.le = 1;
#endif
	pko_command.s.n2 = 1;	/* Don't pollute L2 with the outgoing packet */
	pko_command.s.segs = 1;
	pko_command.s.total_bytes = skb->len;
	pko_command.s.size0 = CVMX_FAU_OP_SIZE_32;
	pko_command.s.subone0 = 1;

	pko_command.s.dontfree = 1;

	/* Build the PKO buffer pointer */
	hw_buffer.u64 = 0;
	if (skb_shinfo(skb)->nr_frags == 0) {
		hw_buffer.s.addr = XKPHYS_TO_PHYS((u64)skb->data);
		hw_buffer.s.pool = 0;
		hw_buffer.s.size = skb->len;
	} else {
		hw_buffer.s.addr = XKPHYS_TO_PHYS((u64)skb->data);
		hw_buffer.s.pool = 0;
		hw_buffer.s.size = skb_headlen(skb);
		CVM_OCT_SKB_CB(skb)[0] = hw_buffer.u64;
		for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
			struct skb_frag_struct *fs = skb_shinfo(skb)->frags + i;

			hw_buffer.s.addr = XKPHYS_TO_PHYS(
				(u64)(page_address(fs->page.p) +
				fs->page_offset));
			hw_buffer.s.size = fs->size;
			CVM_OCT_SKB_CB(skb)[i + 1] = hw_buffer.u64;
		}
		hw_buffer.s.addr = XKPHYS_TO_PHYS((u64)CVM_OCT_SKB_CB(skb));
		hw_buffer.s.size = skb_shinfo(skb)->nr_frags + 1;
		pko_command.s.segs = skb_shinfo(skb)->nr_frags + 1;
		pko_command.s.gather = 1;
		goto dont_put_skbuff_in_hw;
	}

	/*
	 * See if we can put this skb in the FPA pool. Any strange
	 * behavior from the Linux networking stack will most likely
	 * be caused by a bug in the following code. If some field is
	 * in use by the network stack and gets carried over when a
	 * buffer is reused, bad things may happen.  If in doubt and
	 * you dont need the absolute best performance, disable the
	 * define REUSE_SKBUFFS_WITHOUT_FREE. The reuse of buffers has
	 * shown a 25% increase in performance under some loads.
	 */
#if REUSE_SKBUFFS_WITHOUT_FREE
	fpa_head = skb->head + 256 - ((unsigned long)skb->head & 0x7f);
	if (unlikely(skb->data < fpa_head)) {
		/* TX buffer beginning can't meet FPA alignment constraints */
		goto dont_put_skbuff_in_hw;
	}
	if (unlikely
	    ((skb_end_pointer(skb) - fpa_head) < CVMX_FPA_PACKET_POOL_SIZE)) {
		/* TX buffer isn't large enough for the FPA */
		goto dont_put_skbuff_in_hw;
	}
	if (unlikely(skb_shared(skb))) {
		/* TX buffer sharing data with someone else */
		goto dont_put_skbuff_in_hw;
	}
	if (unlikely(skb_cloned(skb))) {
		/* TX buffer has been cloned */
		goto dont_put_skbuff_in_hw;
	}
	if (unlikely(skb_header_cloned(skb))) {
		/* TX buffer header has been cloned */
		goto dont_put_skbuff_in_hw;
	}
	if (unlikely(skb->destructor)) {
		/* TX buffer has a destructor */
		goto dont_put_skbuff_in_hw;
	}
	if (unlikely(skb_shinfo(skb)->nr_frags)) {
		/* TX buffer has fragments */
		goto dont_put_skbuff_in_hw;
	}
	if (unlikely
	    (skb->truesize !=
	     sizeof(*skb) + skb_end_offset(skb))) {
		/* TX buffer truesize has been changed */
		goto dont_put_skbuff_in_hw;
	}

	/*
	 * We can use this buffer in the FPA.  We don't need the FAU
	 * update anymore
	 */
	pko_command.s.dontfree = 0;

	hw_buffer.s.back = ((unsigned long)skb->data >> 7) -
			   ((unsigned long)fpa_head >> 7);

	*(struct sk_buff **)(fpa_head - sizeof(void *)) = skb;

	/*
	 * The skbuff will be reused without ever being freed. We must
	 * cleanup a bunch of core things.
	 */
	dst_release(skb_dst(skb));
	skb_dst_set(skb, NULL);
#ifdef CONFIG_XFRM
	secpath_put(skb->sp);
	skb->sp = NULL;
#endif
	nf_reset(skb);

#ifdef CONFIG_NET_SCHED
	skb->tc_index = 0;
	skb_reset_tc(skb);
#endif /* CONFIG_NET_SCHED */
#endif /* REUSE_SKBUFFS_WITHOUT_FREE */

dont_put_skbuff_in_hw:

	/* Check if we can use the hardware checksumming */
	if ((skb->protocol == htons(ETH_P_IP)) &&
	    (ip_hdr(skb)->version == 4) &&
	    (ip_hdr(skb)->ihl == 5) &&
	    ((ip_hdr(skb)->frag_off == 0) ||
	     (ip_hdr(skb)->frag_off == htons(1 << 14))) &&
	    ((ip_hdr(skb)->protocol == IPPROTO_TCP) ||
	     (ip_hdr(skb)->protocol == IPPROTO_UDP))) {
		/* Use hardware checksum calc */
		pko_command.s.ipoffp1 = skb_network_offset(skb) + 1;
	}

	if (USE_ASYNC_IOBDMA) {
		/* Get the number of skbuffs in use by the hardware */
		CVMX_SYNCIOBDMA;
		skb_to_free = cvmx_scratch_read64(CVMX_SCR_SCRATCH);
		buffers_to_free = cvmx_scratch_read64(CVMX_SCR_SCRATCH + 8);
	} else {
		/* Get the number of skbuffs in use by the hardware */
		skb_to_free = cvmx_fau_fetch_and_add32(priv->fau + qos * 4,
						       MAX_SKB_TO_FREE);
		buffers_to_free =
		    cvmx_fau_fetch_and_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE, 0);
	}

	skb_to_free = cvm_oct_adjust_skb_to_free(skb_to_free,
						 priv->fau + qos * 4);

	/*
	 * If we're sending faster than the receive can free them then
	 * don't do the HW free.
	 */
	if ((buffers_to_free < -100) && !pko_command.s.dontfree)
		pko_command.s.dontfree = 1;

	if (pko_command.s.dontfree) {
		queue_type = QUEUE_CORE;
		pko_command.s.reg0 = priv->fau + qos * 4;
	} else {
		queue_type = QUEUE_HW;
	}
	if (USE_ASYNC_IOBDMA)
		cvmx_fau_async_fetch_and_add32(
				CVMX_SCR_SCRATCH, FAU_TOTAL_TX_TO_CLEAN, 1);

	spin_lock_irqsave(&priv->tx_free_list[qos].lock, flags);

	/* Drop this packet if we have too many already queued to the HW */
	if (unlikely(skb_queue_len(&priv->tx_free_list[qos]) >=
		     MAX_OUT_QUEUE_DEPTH)) {
		if (dev->tx_queue_len != 0) {
			/* Drop the lock when notifying the core.  */
			spin_unlock_irqrestore(&priv->tx_free_list[qos].lock,
					       flags);
			netif_stop_queue(dev);
			spin_lock_irqsave(&priv->tx_free_list[qos].lock,
					  flags);
		} else {
			/* If not using normal queueing.  */
			queue_type = QUEUE_DROP;
			goto skip_xmit;
		}
	}

	cvmx_pko_send_packet_prepare(priv->port, priv->queue + qos,
				     CVMX_PKO_LOCK_NONE);

	/* Send the packet to the output queue */
	if (unlikely(cvmx_pko_send_packet_finish(priv->port,
						 priv->queue + qos,
						 pko_command, hw_buffer,
						 CVMX_PKO_LOCK_NONE))) {
		printk_ratelimited("%s: Failed to send the packet\n",
				   dev->name);
		queue_type = QUEUE_DROP;
	}
skip_xmit:
	to_free_list = NULL;

	switch (queue_type) {
	case QUEUE_DROP:
		skb->next = to_free_list;
		to_free_list = skb;
		dev->stats.tx_dropped++;
		break;
	case QUEUE_HW:
		cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE, -1);
		break;
	case QUEUE_CORE:
		__skb_queue_tail(&priv->tx_free_list[qos], skb);
		break;
	default:
		BUG();
	}

	while (skb_to_free > 0) {
		struct sk_buff *t = __skb_dequeue(&priv->tx_free_list[qos]);

		t->next = to_free_list;
		to_free_list = t;
		skb_to_free--;
	}

	spin_unlock_irqrestore(&priv->tx_free_list[qos].lock, flags);

	/* Do the actual freeing outside of the lock. */
	while (to_free_list) {
		struct sk_buff *t = to_free_list;

		to_free_list = to_free_list->next;
		dev_kfree_skb_any(t);
	}

	if (USE_ASYNC_IOBDMA) {
		CVMX_SYNCIOBDMA;
		total_to_clean = cvmx_scratch_read64(CVMX_SCR_SCRATCH);
		/* Restore the scratch area */
		cvmx_scratch_write64(CVMX_SCR_SCRATCH, old_scratch);
		cvmx_scratch_write64(CVMX_SCR_SCRATCH + 8, old_scratch2);
	} else {
		total_to_clean = cvmx_fau_fetch_and_add32(
						FAU_TOTAL_TX_TO_CLEAN, 1);
	}

	if (total_to_clean & 0x3ff) {
		/*
		 * Schedule the cleanup tasklet every 1024 packets for
		 * the pathological case of high traffic on one port
		 * delaying clean up of packets on a different port
		 * that is blocked waiting for the cleanup.
		 */
		tasklet_schedule(&cvm_oct_tx_cleanup_tasklet);
	}

	cvm_oct_kick_tx_poll_watchdog();

	return NETDEV_TX_OK;
}