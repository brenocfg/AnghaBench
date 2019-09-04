#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int seq_num; int amsdu; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; struct rx_pkt_attrib attrib; } ;
struct TYPE_6__ {TYPE_2__ hdr; } ;
union recv_frame {TYPE_3__ u; } ;
struct __queue {int dummy; } ;
struct recv_reorder_ctrl {int indicate_seq; struct __queue pending_recvframe_queue; } ;
struct recv_priv {int /*<<< orphan*/  free_recv_queue; } ;
struct list_head {int dummy; } ;
struct debug_priv {int /*<<< orphan*/  dbg_rx_ampdu_forced_indicate_count; } ;
struct dvobj_priv {struct debug_priv drv_dbg; } ;
struct TYPE_4__ {int /*<<< orphan*/  core_rx_post_indicate_in_oder; } ;
struct adapter {int bDriverStopped; int bSurpriseRemoved; TYPE_1__ rx_logs; struct dvobj_priv* dvobj; struct recv_priv recvpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SN_EQUAL (int,int) ; 
 int /*<<< orphan*/  SN_LESS (int,int) ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 scalar_t__ amsdu_to_msdu (struct adapter*,union recv_frame*) ; 
 struct list_head* get_list_head (struct __queue*) ; 
 struct list_head* get_next (struct list_head*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  recv_indicatepkts_pkt_loss_cnt (struct debug_priv*,int,int) ; 
 int /*<<< orphan*/  rtw_free_recvframe (union recv_frame*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_recv_indicatepkt (struct adapter*,union recv_frame*) ; 

int recv_indicatepkts_in_order(struct adapter *padapter, struct recv_reorder_ctrl *preorder_ctrl, int bforced)
{
	struct list_head	*phead, *plist;
	union recv_frame *prframe;
	struct rx_pkt_attrib *pattrib;
	/* u8 index = 0; */
	int bPktInBuf = false;
	struct recv_priv *precvpriv = &padapter->recvpriv;
	struct __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;
	struct dvobj_priv *psdpriv = padapter->dvobj;
	struct debug_priv *pdbgpriv = &psdpriv->drv_dbg;

	DBG_COUNTER(padapter->rx_logs.core_rx_post_indicate_in_oder);

	/* DbgPrint("+recv_indicatepkts_in_order\n"); */

	/* spin_lock_irqsave(&ppending_recvframe_queue->lock, irql); */
	/* spin_lock(&ppending_recvframe_queue->lock); */

	phead =		get_list_head(ppending_recvframe_queue);
	plist = get_next(phead);

	/*  Handling some condition for forced indicate case. */
	if (bforced == true) {
		pdbgpriv->dbg_rx_ampdu_forced_indicate_count++;
		if (list_empty(phead)) {
			/*  spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql); */
			/* spin_unlock(&ppending_recvframe_queue->lock); */
			return true;
		}

		prframe = (union recv_frame *)plist;
		pattrib = &prframe->u.hdr.attrib;

		#ifdef DBG_RX_SEQ
		DBG_871X("DBG_RX_SEQ %s:%d IndicateSeq: %d, NewSeq: %d\n", __func__, __LINE__,
			preorder_ctrl->indicate_seq, pattrib->seq_num);
		#endif
		recv_indicatepkts_pkt_loss_cnt(pdbgpriv, preorder_ctrl->indicate_seq, pattrib->seq_num);
		preorder_ctrl->indicate_seq = pattrib->seq_num;

	}

	/*  Prepare indication list and indication. */
	/*  Check if there is any packet need indicate. */
	while (!list_empty(phead)) {

		prframe = (union recv_frame *)plist;
		pattrib = &prframe->u.hdr.attrib;

		if (!SN_LESS(preorder_ctrl->indicate_seq, pattrib->seq_num)) {
			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_,
				 ("recv_indicatepkts_in_order: indicate =%d seq =%d amsdu =%d\n",
				  preorder_ctrl->indicate_seq, pattrib->seq_num, pattrib->amsdu));

			plist = get_next(plist);
			list_del_init(&(prframe->u.hdr.list));

			if (SN_EQUAL(preorder_ctrl->indicate_seq, pattrib->seq_num)) {
				preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1) & 0xFFF;
				#ifdef DBG_RX_SEQ
				DBG_871X("DBG_RX_SEQ %s:%d IndicateSeq: %d, NewSeq: %d\n", __func__, __LINE__,
					preorder_ctrl->indicate_seq, pattrib->seq_num);
				#endif
			}

			/* Set this as a lock to make sure that only one thread is indicating packet. */
			/* pTS->RxIndicateState = RXTS_INDICATE_PROCESSING; */

			/*  Indicate packets */
			/* RT_ASSERT((index<=REORDER_WIN_SIZE), ("RxReorderIndicatePacket(): Rx Reorder buffer full!!\n")); */


			/* indicate this recv_frame */
			/* DbgPrint("recv_indicatepkts_in_order, indicate_seq =%d, seq_num =%d\n", precvpriv->indicate_seq, pattrib->seq_num); */
			if (!pattrib->amsdu) {
				/* DBG_871X("recv_indicatepkts_in_order, amsdu!= 1, indicate_seq =%d, seq_num =%d\n", preorder_ctrl->indicate_seq, pattrib->seq_num); */

				if ((padapter->bDriverStopped == false) &&
				    (padapter->bSurpriseRemoved == false))
					rtw_recv_indicatepkt(padapter, prframe);/* indicate this recv_frame */

			} else if (pattrib->amsdu == 1) {
				if (amsdu_to_msdu(padapter, prframe) != _SUCCESS)
					rtw_free_recvframe(prframe, &precvpriv->free_recv_queue);

			} else{
				/* error condition; */
			}


			/* Update local variables. */
			bPktInBuf = false;

		} else{
			bPktInBuf = true;
			break;
		}

		/* DbgPrint("recv_indicatepkts_in_order():while\n"); */

	}

	/* spin_unlock(&ppending_recvframe_queue->lock); */
	/* spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql); */

	return bPktInBuf;
}