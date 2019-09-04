#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int amsdu; int qos; int seq_num; } ;
struct TYPE_9__ {struct recv_reorder_ctrl* preorder_ctrl; struct rx_pkt_attrib attrib; } ;
struct TYPE_10__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;
struct recv_reorder_ctrl {scalar_t__ enable; int indicate_seq; int /*<<< orphan*/  reordering_ctrl_timer; TYPE_3__ pending_recvframe_queue; } ;
typedef  TYPE_3__ _queue ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_12__ {scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; } ;
typedef  TYPE_4__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  REORDER_WAIT_TIME ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 scalar_t__ _FALSE ; 
 int _SUCCESS ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _drv_alert_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int amsdu_to_msdu (TYPE_4__*,union recv_frame*) ; 
 int /*<<< orphan*/  check_indicate_seq (struct recv_reorder_ctrl*,int) ; 
 int /*<<< orphan*/  enqueue_reorder_recvframe (struct recv_reorder_ctrl*,union recv_frame*) ; 
 scalar_t__ recv_indicatepkts_in_order (TYPE_4__*,struct recv_reorder_ctrl*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_recv_indicatepkt (TYPE_4__*,union recv_frame*) ; 
 int /*<<< orphan*/  wlanhdr_to_ethhdr (union recv_frame*) ; 

int recv_indicatepkt_reorder(_adapter *padapter, union recv_frame *prframe)
{
	_irqL irql;
	int retval = _SUCCESS;
	struct rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	struct recv_reorder_ctrl *preorder_ctrl = prframe->u.hdr.preorder_ctrl;
	_queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;

	if(!pattrib->amsdu)
	{
		//s1.
		wlanhdr_to_ethhdr(prframe);

		//if ((pattrib->qos!=1) /*|| pattrib->priority!=0 || IS_MCAST(pattrib->ra)*/
		//	|| (pattrib->eth_type==0x0806) || (pattrib->ack_policy!=0))
		if (pattrib->qos!=1)
		{
			if ((padapter->bDriverStopped == _FALSE) &&
			    (padapter->bSurpriseRemoved == _FALSE))
			{
				RT_TRACE(_module_rtl871x_recv_c_, _drv_alert_, ("@@@@  recv_indicatepkt_reorder -recv_func recv_indicatepkt\n" ));

				rtw_recv_indicatepkt(padapter, prframe);
				return _SUCCESS;

			}
			
			#ifdef DBG_RX_DROP_FRAME
			DBG_871X("DBG_RX_DROP_FRAME %s pattrib->qos !=1\n", __FUNCTION__);
			#endif
			
			return _FAIL;
		
		}

		if (preorder_ctrl->enable == _FALSE)
		{
			//indicate this recv_frame			
			preorder_ctrl->indicate_seq = pattrib->seq_num;
			#ifdef DBG_RX_SEQ
			DBG_871X("DBG_RX_SEQ %s:%d IndicateSeq: %d, NewSeq: %d\n", __FUNCTION__, __LINE__,
				preorder_ctrl->indicate_seq, pattrib->seq_num);
			#endif
			
			rtw_recv_indicatepkt(padapter, prframe);		
			
			preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1)%4096;
			#ifdef DBG_RX_SEQ
			DBG_871X("DBG_RX_SEQ %s:%d IndicateSeq: %d, NewSeq: %d\n", __FUNCTION__, __LINE__,
				preorder_ctrl->indicate_seq, pattrib->seq_num);
			#endif
			
			return _SUCCESS;	
		}			

#ifndef CONFIG_RECV_REORDERING_CTRL
		//indicate this recv_frame
		rtw_recv_indicatepkt(padapter, prframe);
		return _SUCCESS;
#endif

	}
	else if(pattrib->amsdu==1) //temp filter -> means didn't support A-MSDUs in a A-MPDU
	{
		if (preorder_ctrl->enable == _FALSE)
		{
			preorder_ctrl->indicate_seq = pattrib->seq_num;
			#ifdef DBG_RX_SEQ
			DBG_871X("DBG_RX_SEQ %s:%d IndicateSeq: %d, NewSeq: %d\n", __FUNCTION__, __LINE__,
				preorder_ctrl->indicate_seq, pattrib->seq_num);
			#endif

			retval = amsdu_to_msdu(padapter, prframe);

			preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1)%4096;
			#ifdef DBG_RX_SEQ
			DBG_871X("DBG_RX_SEQ %s:%d IndicateSeq: %d, NewSeq: %d\n", __FUNCTION__, __LINE__,
				preorder_ctrl->indicate_seq, pattrib->seq_num);
			#endif

			if(retval != _SUCCESS){
				#ifdef DBG_RX_DROP_FRAME
				DBG_871X("DBG_RX_DROP_FRAME %s amsdu_to_msdu fail\n", __FUNCTION__);
				#endif
			}

			return retval;
		}
	}
	else
	{

	}

	_enter_critical_bh(&ppending_recvframe_queue->lock, &irql);

	RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_,
		 ("recv_indicatepkt_reorder: indicate=%d seq=%d\n",
		  preorder_ctrl->indicate_seq, pattrib->seq_num));

	//s2. check if winstart_b(indicate_seq) needs to been updated
	if(!check_indicate_seq(preorder_ctrl, pattrib->seq_num))
	{
		//pHTInfo->RxReorderDropCounter++;
		//ReturnRFDList(Adapter, pRfd);
		//RT_TRACE(COMP_RX_REORDER, DBG_TRACE, ("RxReorderIndicatePacket() ==> Packet Drop!!\n"));
		//_exit_critical_ex(&ppending_recvframe_queue->lock, &irql);
		//return _FAIL;

		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s check_indicate_seq fail\n", __FUNCTION__);
		#endif
#if 0		
		rtw_recv_indicatepkt(padapter, prframe);

		_exit_critical_bh(&ppending_recvframe_queue->lock, &irql);
		
		goto _success_exit;
#else
		goto _err_exit;
#endif
	}


	//s3. Insert all packet into Reorder Queue to maintain its ordering.
	if(!enqueue_reorder_recvframe(preorder_ctrl, prframe))
	{
		//DbgPrint("recv_indicatepkt_reorder, enqueue_reorder_recvframe fail!\n");
		//_exit_critical_ex(&ppending_recvframe_queue->lock, &irql);
		//return _FAIL;
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s enqueue_reorder_recvframe fail\n", __FUNCTION__);
		#endif
		goto _err_exit;
	}


	//s4.
	// Indication process.
	// After Packet dropping and Sliding Window shifting as above, we can now just indicate the packets
	// with the SeqNum smaller than latest WinStart and buffer other packets.
	//
	// For Rx Reorder condition:
	// 1. All packets with SeqNum smaller than WinStart => Indicate
	// 2. All packets with SeqNum larger than or equal to WinStart => Buffer it.
	//

	//recv_indicatepkts_in_order(padapter, preorder_ctrl, _TRUE);
	if(recv_indicatepkts_in_order(padapter, preorder_ctrl, _FALSE)==_TRUE)
	{
		_set_timer(&preorder_ctrl->reordering_ctrl_timer, REORDER_WAIT_TIME);
		_exit_critical_bh(&ppending_recvframe_queue->lock, &irql);
	}
	else
	{
		_exit_critical_bh(&ppending_recvframe_queue->lock, &irql);
		_cancel_timer_ex(&preorder_ctrl->reordering_ctrl_timer);
	}


_success_exit:

	return _SUCCESS;

_err_exit:

        _exit_critical_bh(&ppending_recvframe_queue->lock, &irql);

	return _FAIL;
}