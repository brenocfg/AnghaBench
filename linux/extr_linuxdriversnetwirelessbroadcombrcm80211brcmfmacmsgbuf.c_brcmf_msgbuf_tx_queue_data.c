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
struct sk_buff {int /*<<< orphan*/  priority; scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;
struct brcmf_pub {TYPE_1__* proto; } ;
struct brcmf_msgbuf {struct brcmf_flowring* flow; } ;
struct brcmf_flowring {int dummy; } ;
struct TYPE_2__ {scalar_t__ pd; } ;

/* Variables and functions */
 scalar_t__ BRCMF_FLOWRING_INVALID_ID ; 
 scalar_t__ BRCMF_MSGBUF_TRICKLE_TXWORKER_THRS ; 
 int ENOMEM ; 
 scalar_t__ brcmf_flowring_enqueue (struct brcmf_flowring*,scalar_t__,struct sk_buff*) ; 
 scalar_t__ brcmf_flowring_lookup (struct brcmf_flowring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ brcmf_msgbuf_flowring_create (struct brcmf_msgbuf*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_schedule_txdata (struct brcmf_msgbuf*,scalar_t__,int) ; 

__attribute__((used)) static int brcmf_msgbuf_tx_queue_data(struct brcmf_pub *drvr, int ifidx,
				      struct sk_buff *skb)
{
	struct brcmf_msgbuf *msgbuf = (struct brcmf_msgbuf *)drvr->proto->pd;
	struct brcmf_flowring *flow = msgbuf->flow;
	struct ethhdr *eh = (struct ethhdr *)(skb->data);
	u32 flowid;
	u32 queue_count;
	bool force;

	flowid = brcmf_flowring_lookup(flow, eh->h_dest, skb->priority, ifidx);
	if (flowid == BRCMF_FLOWRING_INVALID_ID) {
		flowid = brcmf_msgbuf_flowring_create(msgbuf, ifidx, skb);
		if (flowid == BRCMF_FLOWRING_INVALID_ID)
			return -ENOMEM;
	}
	queue_count = brcmf_flowring_enqueue(flow, flowid, skb);
	force = ((queue_count % BRCMF_MSGBUF_TRICKLE_TXWORKER_THRS) == 0);
	brcmf_msgbuf_schedule_txdata(msgbuf, flowid, force);

	return 0;
}