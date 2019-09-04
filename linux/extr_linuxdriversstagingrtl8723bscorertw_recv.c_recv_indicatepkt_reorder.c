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
struct rx_pkt_attrib {int amsdu; int qos; int seq_num; } ;
struct TYPE_4__ {struct recv_reorder_ctrl* preorder_ctrl; struct rx_pkt_attrib attrib; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct __queue {int /*<<< orphan*/  lock; } ;
struct recv_reorder_ctrl {int enable; int indicate_seq; int /*<<< orphan*/  reordering_ctrl_timer; struct __queue pending_recvframe_queue; } ;
struct debug_priv {int /*<<< orphan*/  dbg_rx_ampdu_drop_count; } ;
struct dvobj_priv {struct debug_priv drv_dbg; } ;
struct TYPE_6__ {int /*<<< orphan*/  core_rx_post_indicate_reoder; } ;
struct adapter {int bDriverStopped; int bSurpriseRemoved; TYPE_3__ rx_logs; struct dvobj_priv* dvobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REORDER_WAIT_TIME ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int amsdu_to_msdu (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  check_indicate_seq (struct recv_reorder_ctrl*,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enqueue_reorder_recvframe (struct recv_reorder_ctrl*,union recv_frame*) ; 
 int recv_indicatepkts_in_order (struct adapter*,struct recv_reorder_ctrl*,int) ; 
 int /*<<< orphan*/  rtw_recv_indicatepkt (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlanhdr_to_ethhdr (union recv_frame*) ; 

int recv_indicatepkt_reorder(struct adapter *padapter, union recv_frame *prframe)
{
	int retval = _SUCCESS;
	struct rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	struct recv_reorder_ctrl *preorder_ctrl = prframe->u.hdr.preorder_ctrl;
	struct __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;
	struct dvobj_priv *psdpriv = padapter->dvobj;
	struct debug_priv *pdbgpriv = &psdpriv->drv_dbg;

	DBG_COUNTER(padapter->rx_logs.core_rx_post_indicate_reoder);

	if (!pattrib->amsdu) {
		/* s1. */
		wlanhdr_to_ethhdr(prframe);

		if (pattrib->qos != 1) {
			if ((padapter->bDriverStopped == false) &&
			    (padapter->bSurpriseRemoved == false)) {
				RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("@@@@  recv_indicatepkt_reorder -recv_func recv_indicatepkt\n"));

				rtw_recv_indicatepkt(padapter, prframe);
				return _SUCCESS;

			}

			#ifdef DBG_RX_DROP_FRAME
			DBG_871X("DBG_RX_DROP_FRAME %s pattrib->qos != 1\n", __func__);
			#endif

			return _FAIL;

		}

		if (preorder_ctrl->enable == false) {
			/* indicate this recv_frame */
			preorder_ctrl->indicate_seq = pattrib->seq_num;
			#ifdef DBG_RX_SEQ
			DBG_871X("DBG_RX_SEQ %s:%d IndicateSeq: %d, NewSeq: %d\n", __func__, __LINE__,
				preorder_ctrl->indicate_seq, pattrib->seq_num);
			#endif

			rtw_recv_indicatepkt(padapter, prframe);

			preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1)%4096;
			#ifdef DBG_RX_SEQ
			DBG_871X("DBG_RX_SEQ %s:%d IndicateSeq: %d, NewSeq: %d\n", __func__, __LINE__,
				preorder_ctrl->indicate_seq, pattrib->seq_num);
			#endif

			return _SUCCESS;
		}
	} else if (pattrib->amsdu == 1) { /* temp filter -> means didn't support A-MSDUs in a A-MPDU */
		if (preorder_ctrl->enable == false) {
			preorder_ctrl->indicate_seq = pattrib->seq_num;
			#ifdef DBG_RX_SEQ
			DBG_871X("DBG_RX_SEQ %s:%d IndicateSeq: %d, NewSeq: %d\n", __func__, __LINE__,
				preorder_ctrl->indicate_seq, pattrib->seq_num);
			#endif

			retval = amsdu_to_msdu(padapter, prframe);

			preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1)%4096;
			#ifdef DBG_RX_SEQ
			DBG_871X("DBG_RX_SEQ %s:%d IndicateSeq: %d, NewSeq: %d\n", __func__, __LINE__,
				preorder_ctrl->indicate_seq, pattrib->seq_num);
			#endif

			if (retval != _SUCCESS) {
				#ifdef DBG_RX_DROP_FRAME
				DBG_871X("DBG_RX_DROP_FRAME %s amsdu_to_msdu fail\n", __func__);
				#endif
			}

			return retval;
		}
	}

	spin_lock_bh(&ppending_recvframe_queue->lock);

	RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_,
		 ("recv_indicatepkt_reorder: indicate =%d seq =%d\n",
		  preorder_ctrl->indicate_seq, pattrib->seq_num));

	/* s2. check if winstart_b(indicate_seq) needs to been updated */
	if (!check_indicate_seq(preorder_ctrl, pattrib->seq_num)) {
		pdbgpriv->dbg_rx_ampdu_drop_count++;
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s check_indicate_seq fail\n", __func__);
		#endif
		goto _err_exit;
	}


	/* s3. Insert all packet into Reorder Queue to maintain its ordering. */
	if (!enqueue_reorder_recvframe(preorder_ctrl, prframe)) {
		/* DbgPrint("recv_indicatepkt_reorder, enqueue_reorder_recvframe fail!\n"); */
		/* spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql); */
		/* return _FAIL; */
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s enqueue_reorder_recvframe fail\n", __func__);
		#endif
		goto _err_exit;
	}


	/* s4. */
	/*  Indication process. */
	/*  After Packet dropping and Sliding Window shifting as above, we can now just indicate the packets */
	/*  with the SeqNum smaller than latest WinStart and buffer other packets. */
	/*  */
	/*  For Rx Reorder condition: */
	/*  1. All packets with SeqNum smaller than WinStart => Indicate */
	/*  2. All packets with SeqNum larger than or equal to WinStart => Buffer it. */
	/*  */

	/* recv_indicatepkts_in_order(padapter, preorder_ctrl, true); */
	if (recv_indicatepkts_in_order(padapter, preorder_ctrl, false) == true) {
		_set_timer(&preorder_ctrl->reordering_ctrl_timer, REORDER_WAIT_TIME);
		spin_unlock_bh(&ppending_recvframe_queue->lock);
	} else{
		spin_unlock_bh(&ppending_recvframe_queue->lock);
		del_timer_sync(&preorder_ctrl->reordering_ctrl_timer);
	}

	return _SUCCESS;

_err_exit:
	spin_unlock_bh(&ppending_recvframe_queue->lock);

	return _FAIL;
}