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
typedef  int /*<<< orphan*/  ulong ;
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  priority; scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;
struct brcmf_msgbuf_work_item {int ifidx; int /*<<< orphan*/  queue; int /*<<< orphan*/  da; int /*<<< orphan*/  sa; scalar_t__ flowid; } ;
struct brcmf_msgbuf {int /*<<< orphan*/  flowring_work; int /*<<< orphan*/  flowring_work_lock; int /*<<< orphan*/  work_queue; int /*<<< orphan*/  flow; } ;

/* Variables and functions */
 scalar_t__ BRCMF_FLOWRING_INVALID_ID ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ brcmf_flowring_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct brcmf_msgbuf_work_item*) ; 
 struct brcmf_msgbuf_work_item* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 brcmf_msgbuf_flowring_create(struct brcmf_msgbuf *msgbuf, int ifidx,
					struct sk_buff *skb)
{
	struct brcmf_msgbuf_work_item *create;
	struct ethhdr *eh = (struct ethhdr *)(skb->data);
	u32 flowid;
	ulong flags;

	create = kzalloc(sizeof(*create), GFP_ATOMIC);
	if (create == NULL)
		return BRCMF_FLOWRING_INVALID_ID;

	flowid = brcmf_flowring_create(msgbuf->flow, eh->h_dest,
				       skb->priority, ifidx);
	if (flowid == BRCMF_FLOWRING_INVALID_ID) {
		kfree(create);
		return flowid;
	}

	create->flowid = flowid;
	create->ifidx = ifidx;
	memcpy(create->sa, eh->h_source, ETH_ALEN);
	memcpy(create->da, eh->h_dest, ETH_ALEN);

	spin_lock_irqsave(&msgbuf->flowring_work_lock, flags);
	list_add_tail(&create->queue, &msgbuf->work_queue);
	spin_unlock_irqrestore(&msgbuf->flowring_work_lock, flags);
	schedule_work(&msgbuf->flowring_work);

	return flowid;
}