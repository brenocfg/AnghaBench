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
struct rx_pkt_attrib {int /*<<< orphan*/  seq_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; struct rx_pkt_attrib attrib; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct __queue {int dummy; } ;
struct recv_reorder_ctrl {struct __queue pending_recvframe_queue; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ SN_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SN_LESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct list_head* get_list_head (struct __queue*) ; 
 struct list_head* get_next (struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

int enqueue_reorder_recvframe(struct recv_reorder_ctrl *preorder_ctrl, union recv_frame *prframe)
{
	struct rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	struct __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;
	struct list_head	*phead, *plist;
	union recv_frame *pnextrframe;
	struct rx_pkt_attrib *pnextattrib;

	/* DbgPrint("+enqueue_reorder_recvframe()\n"); */

	/* spin_lock_irqsave(&ppending_recvframe_queue->lock, irql); */
	/* spin_lock(&ppending_recvframe_queue->lock); */


	phead = get_list_head(ppending_recvframe_queue);
	plist = get_next(phead);

	while (phead != plist) {
		pnextrframe = (union recv_frame *)plist;
		pnextattrib = &pnextrframe->u.hdr.attrib;

		if (SN_LESS(pnextattrib->seq_num, pattrib->seq_num))
			plist = get_next(plist);
		else if (SN_EQUAL(pnextattrib->seq_num, pattrib->seq_num))
			/* Duplicate entry is found!! Do not insert current entry. */
			/* RT_TRACE(COMP_RX_REORDER, DBG_TRACE, ("InsertRxReorderList(): Duplicate packet is dropped!! IndicateSeq: %d, NewSeq: %d\n", pTS->RxIndicateSeq, SeqNum)); */
			/* spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql); */
			return false;
		else
			break;

		/* DbgPrint("enqueue_reorder_recvframe():while\n"); */

	}


	/* spin_lock_irqsave(&ppending_recvframe_queue->lock, irql); */
	/* spin_lock(&ppending_recvframe_queue->lock); */

	list_del_init(&(prframe->u.hdr.list));

	list_add_tail(&(prframe->u.hdr.list), plist);

	/* spin_unlock(&ppending_recvframe_queue->lock); */
	/* spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql); */


	/* RT_TRACE(COMP_RX_REORDER, DBG_TRACE, ("InsertRxReorderList(): Pkt insert into buffer!! IndicateSeq: %d, NewSeq: %d\n", pTS->RxIndicateSeq, SeqNum)); */
	return true;

}