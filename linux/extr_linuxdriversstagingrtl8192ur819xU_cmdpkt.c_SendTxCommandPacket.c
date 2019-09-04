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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ cb; } ;
struct r8192_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct cb_desc {size_t queue_index; scalar_t__ txbuf_size; scalar_t__ bLastIniPkt; int /*<<< orphan*/  bCmdOrInit; } ;
typedef  int /*<<< orphan*/  rt_status ;
typedef  int /*<<< orphan*/  dev ;
struct TYPE_2__ {int /*<<< orphan*/  (* softmac_hard_start_xmit ) (struct sk_buff*,struct net_device*) ;int /*<<< orphan*/ * skb_waitQ; scalar_t__ queue_stop; int /*<<< orphan*/  (* check_nic_enough_desc ) (struct net_device*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_FIRMWARE ; 
 int /*<<< orphan*/  DESC_PACKET_TYPE_NORMAL ; 
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 int /*<<< orphan*/  RT_STATUS_FAILURE ; 
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 size_t TXCMD_QUEUE ; 
 scalar_t__ USB_HWDESC_HEADER_LEN ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,struct net_device**,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,size_t) ; 
 int /*<<< orphan*/  stub2 (struct sk_buff*,struct net_device*) ; 

rt_status SendTxCommandPacket(struct net_device *dev, void *pData, u32 DataLen)
{
	struct r8192_priv   *priv = ieee80211_priv(dev);
	struct sk_buff	    *skb;
	struct cb_desc	    *tcb_desc;

	/* Get TCB and local buffer from common pool.
	 * (It is shared by CmdQ, MgntQ, and USB coalesce DataQ)
	 */
	skb  = dev_alloc_skb(USB_HWDESC_HEADER_LEN + DataLen + 4);
	if (!skb)
		return RT_STATUS_FAILURE;
	memcpy((unsigned char *)(skb->cb), &dev, sizeof(dev));
	tcb_desc = (struct cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	tcb_desc->queue_index = TXCMD_QUEUE;
	tcb_desc->bCmdOrInit = DESC_PACKET_TYPE_NORMAL;
	tcb_desc->bLastIniPkt = 0;
	skb_reserve(skb, USB_HWDESC_HEADER_LEN);
	skb_put_data(skb, pData, DataLen);
	tcb_desc->txbuf_size = (u16)DataLen;

	if (!priv->ieee80211->check_nic_enough_desc(dev, tcb_desc->queue_index) ||
	    (!skb_queue_empty(&priv->ieee80211->skb_waitQ[tcb_desc->queue_index])) ||
	    (priv->ieee80211->queue_stop)) {
		RT_TRACE(COMP_FIRMWARE, "=== NULL packet ======> tx full!\n");
		skb_queue_tail(&priv->ieee80211->skb_waitQ[tcb_desc->queue_index], skb);
	} else {
		priv->ieee80211->softmac_hard_start_xmit(skb, dev);
	}

	return RT_STATUS_SUCCESS;
}