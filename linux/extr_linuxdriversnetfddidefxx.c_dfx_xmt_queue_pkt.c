#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  void* u32 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct net_device {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_13__ {struct sk_buff* p_skb; } ;
typedef  TYPE_4__ XMT_DRIVER_DESCR ;
struct TYPE_11__ {size_t xmt_prod; size_t xmt_comp; } ;
struct TYPE_12__ {int /*<<< orphan*/  lword; TYPE_2__ index; } ;
struct TYPE_15__ {scalar_t__ link_available; int /*<<< orphan*/  lock; TYPE_3__ rcv_xmt_reg; TYPE_4__* xmt_drv_descr_blk; TYPE_1__* descr_block_virt; int /*<<< orphan*/  bus_dev; int /*<<< orphan*/  xmt_discards; int /*<<< orphan*/  xmt_length_errors; } ;
struct TYPE_14__ {void* long_1; void* long_0; } ;
struct TYPE_10__ {TYPE_5__* xmt_data; } ;
typedef  TYPE_5__ PI_XMT_DESCR ;
typedef  TYPE_6__ DFX_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  DFX_PRH0_BYTE ; 
 int /*<<< orphan*/  DFX_PRH1_BYTE ; 
 int /*<<< orphan*/  DFX_PRH2_BYTE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FDDI_K_LLC_LEN ; 
 int /*<<< orphan*/  FDDI_K_LLC_ZLEN ; 
 int /*<<< orphan*/  IN_RANGE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ PI_K_FALSE ; 
 scalar_t__ PI_K_TRUE ; 
 int /*<<< orphan*/  PI_PDQ_K_REG_TYPE_2_PROD ; 
 scalar_t__ PI_STATE_K_LINK_AVAIL ; 
 int PI_XMT_DESCR_M_EOP ; 
 int PI_XMT_DESCR_M_SOP ; 
 int PI_XMT_DESCR_V_SEG_LEN ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ dfx_hw_adap_state_rd (TYPE_6__*) ; 
 int /*<<< orphan*/  dfx_port_write_long (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_6__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t dfx_xmt_queue_pkt(struct sk_buff *skb,
				     struct net_device *dev)
	{
	DFX_board_t		*bp = netdev_priv(dev);
	u8			prod;				/* local transmit producer index */
	PI_XMT_DESCR		*p_xmt_descr;		/* ptr to transmit descriptor block entry */
	XMT_DRIVER_DESCR	*p_xmt_drv_descr;	/* ptr to transmit driver descriptor */
	dma_addr_t		dma_addr;
	unsigned long		flags;

	netif_stop_queue(dev);

	/*
	 * Verify that incoming transmit request is OK
	 *
	 * Note: The packet size check is consistent with other
	 *		 Linux device drivers, although the correct packet
	 *		 size should be verified before calling the
	 *		 transmit routine.
	 */

	if (!IN_RANGE(skb->len, FDDI_K_LLC_ZLEN, FDDI_K_LLC_LEN))
	{
		printk("%s: Invalid packet length - %u bytes\n",
			dev->name, skb->len);
		bp->xmt_length_errors++;		/* bump error counter */
		netif_wake_queue(dev);
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;			/* return "success" */
	}
	/*
	 * See if adapter link is available, if not, free buffer
	 *
	 * Note: If the link isn't available, free buffer and return 0
	 *		 rather than tell the upper layer to requeue the packet.
	 *		 The methodology here is that by the time the link
	 *		 becomes available, the packet to be sent will be
	 *		 fairly stale.  By simply dropping the packet, the
	 *		 higher layer protocols will eventually time out
	 *		 waiting for response packets which it won't receive.
	 */

	if (bp->link_available == PI_K_FALSE)
		{
		if (dfx_hw_adap_state_rd(bp) == PI_STATE_K_LINK_AVAIL)	/* is link really available? */
			bp->link_available = PI_K_TRUE;		/* if so, set flag and continue */
		else
			{
			bp->xmt_discards++;					/* bump error counter */
			dev_kfree_skb(skb);		/* free sk_buff now */
			netif_wake_queue(dev);
			return NETDEV_TX_OK;		/* return "success" */
			}
		}

	/* Write the three PRH bytes immediately before the FC byte */

	skb_push(skb, 3);
	skb->data[0] = DFX_PRH0_BYTE;	/* these byte values are defined */
	skb->data[1] = DFX_PRH1_BYTE;	/* in the Motorola FDDI MAC chip */
	skb->data[2] = DFX_PRH2_BYTE;	/* specification */

	dma_addr = dma_map_single(bp->bus_dev, skb->data, skb->len,
				  DMA_TO_DEVICE);
	if (dma_mapping_error(bp->bus_dev, dma_addr)) {
		skb_pull(skb, 3);
		return NETDEV_TX_BUSY;
	}

	spin_lock_irqsave(&bp->lock, flags);

	/* Get the current producer and the next free xmt data descriptor */

	prod		= bp->rcv_xmt_reg.index.xmt_prod;
	p_xmt_descr = &(bp->descr_block_virt->xmt_data[prod]);

	/*
	 * Get pointer to auxiliary queue entry to contain information
	 * for this packet.
	 *
	 * Note: The current xmt producer index will become the
	 *	 current xmt completion index when we complete this
	 *	 packet later on.  So, we'll get the pointer to the
	 *	 next auxiliary queue entry now before we bump the
	 *	 producer index.
	 */

	p_xmt_drv_descr = &(bp->xmt_drv_descr_blk[prod++]);	/* also bump producer index */

	/*
	 * Write the descriptor with buffer info and bump producer
	 *
	 * Note: Since we need to start DMA from the packet request
	 *		 header, we'll add 3 bytes to the DMA buffer length,
	 *		 and we'll determine the physical address of the
	 *		 buffer from the PRH, not skb->data.
	 *
	 * Assumptions:
	 *		 1. Packet starts with the frame control (FC) byte
	 *		    at skb->data.
	 *		 2. The 4-byte CRC is not appended to the buffer or
	 *			included in the length.
	 *		 3. Packet length (skb->len) is from FC to end of
	 *			data, inclusive.
	 *		 4. The packet length does not exceed the maximum
	 *			FDDI LLC frame length of 4491 bytes.
	 *		 5. The entire packet is contained in a physically
	 *			contiguous, non-cached, locked memory space
	 *			comprised of a single buffer pointed to by
	 *			skb->data.
	 *		 6. The physical address of the start of packet
	 *			can be determined from the virtual address
	 *			by using pci_map_single() and is only 32-bits
	 *			wide.
	 */

	p_xmt_descr->long_0	= (u32) (PI_XMT_DESCR_M_SOP | PI_XMT_DESCR_M_EOP | ((skb->len) << PI_XMT_DESCR_V_SEG_LEN));
	p_xmt_descr->long_1 = (u32)dma_addr;

	/*
	 * Verify that descriptor is actually available
	 *
	 * Note: If descriptor isn't available, return 1 which tells
	 *	 the upper layer to requeue the packet for later
	 *	 transmission.
	 *
	 *       We need to ensure that the producer never reaches the
	 *	 completion, except to indicate that the queue is empty.
	 */

	if (prod == bp->rcv_xmt_reg.index.xmt_comp)
	{
		skb_pull(skb,3);
		spin_unlock_irqrestore(&bp->lock, flags);
		return NETDEV_TX_BUSY;	/* requeue packet for later */
	}

	/*
	 * Save info for this packet for xmt done indication routine
	 *
	 * Normally, we'd save the producer index in the p_xmt_drv_descr
	 * structure so that we'd have it handy when we complete this
	 * packet later (in dfx_xmt_done).  However, since the current
	 * transmit architecture guarantees a single fragment for the
	 * entire packet, we can simply bump the completion index by
	 * one (1) for each completed packet.
	 *
	 * Note: If this assumption changes and we're presented with
	 *	 an inconsistent number of transmit fragments for packet
	 *	 data, we'll need to modify this code to save the current
	 *	 transmit producer index.
	 */

	p_xmt_drv_descr->p_skb = skb;

	/* Update Type 2 register */

	bp->rcv_xmt_reg.index.xmt_prod = prod;
	dfx_port_write_long(bp, PI_PDQ_K_REG_TYPE_2_PROD, bp->rcv_xmt_reg.lword);
	spin_unlock_irqrestore(&bp->lock, flags);
	netif_wake_queue(dev);
	return NETDEV_TX_OK;	/* packet queued to adapter */
	}