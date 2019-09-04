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
struct TYPE_4__ {int /*<<< orphan*/  th_last_seq; } ;
struct TYPE_3__ {int th_seg; int th_blk_flag; int th_is_xid; int th_seq_num; int /*<<< orphan*/  th_ch_flag; } ;
struct th_sweep {TYPE_2__ sw; TYPE_1__ th; } ;
struct sk_buff {int dummy; } ;
struct net_device {struct ctcm_priv* ml_priv; } ;
struct mpc_group {int in_sweep; int /*<<< orphan*/  fsm; int /*<<< orphan*/ * active_channels; int /*<<< orphan*/  sweep_req_pend_num; int /*<<< orphan*/  sweep_rsp_pend_num; } ;
struct ctcm_priv {struct channel** channel; struct mpc_group* mpcg; } ;
struct channel {int /*<<< orphan*/  sweep_timer; int /*<<< orphan*/  sweep_queue; int /*<<< orphan*/  th_seq_num; struct net_device* netdev; } ;

/* Variables and functions */
 size_t CTCM_READ ; 
 size_t CTCM_WRITE ; 
 int /*<<< orphan*/  CTC_EVENT_RSWEEP_TIMER ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int /*<<< orphan*/  MPCG_EVENT_INOP ; 
 int /*<<< orphan*/  MPC_BUFSIZE_DEFAULT ; 
 int /*<<< orphan*/  TH_SWEEP_LENGTH ; 
 int /*<<< orphan*/  TH_SWEEP_REQ ; 
 struct sk_buff* __dev_alloc_skb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctcm_clear_busy (struct net_device*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  fsm_addtimer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct channel*) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  gfp_type () ; 
 int /*<<< orphan*/  kfree (struct th_sweep*) ; 
 struct th_sweep* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,struct th_sweep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void ctcmpc_send_sweep_req(struct channel *rch)
{
	struct net_device *dev = rch->netdev;
	struct ctcm_priv *priv;
	struct mpc_group *grp;
	struct th_sweep *header;
	struct sk_buff *sweep_skb;
	struct channel *ch;
	/* int rc = 0; */

	priv = dev->ml_priv;
	grp = priv->mpcg;
	ch = priv->channel[CTCM_WRITE];

	/* sweep processing is not complete until response and request */
	/* has completed for all read channels in group		       */
	if (grp->in_sweep == 0) {
		grp->in_sweep = 1;
		grp->sweep_rsp_pend_num = grp->active_channels[CTCM_READ];
		grp->sweep_req_pend_num = grp->active_channels[CTCM_READ];
	}

	sweep_skb = __dev_alloc_skb(MPC_BUFSIZE_DEFAULT, GFP_ATOMIC|GFP_DMA);

	if (sweep_skb == NULL)	{
		/* rc = -ENOMEM; */
				goto nomem;
	}

	header = kmalloc(TH_SWEEP_LENGTH, gfp_type());

	if (!header) {
		dev_kfree_skb_any(sweep_skb);
		/* rc = -ENOMEM; */
				goto nomem;
	}

	header->th.th_seg	= 0x00 ;
	header->th.th_ch_flag	= TH_SWEEP_REQ;  /* 0x0f */
	header->th.th_blk_flag	= 0x00;
	header->th.th_is_xid	= 0x00;
	header->th.th_seq_num	= 0x00;
	header->sw.th_last_seq	= ch->th_seq_num;

	skb_put_data(sweep_skb, header, TH_SWEEP_LENGTH);

	kfree(header);

	netif_trans_update(dev);
	skb_queue_tail(&ch->sweep_queue, sweep_skb);

	fsm_addtimer(&ch->sweep_timer, 100, CTC_EVENT_RSWEEP_TIMER, ch);

	return;

nomem:
	grp->in_sweep = 0;
	ctcm_clear_busy(dev);
	fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);

	return;
}