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
struct TYPE_4__ {int /*<<< orphan*/ * adapter; } ;
struct TYPE_5__ {TYPE_1__ hdr; int /*<<< orphan*/  list; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct recv_priv {int free_recvframe_cnt; scalar_t__ read_port_complete_other_urb_err_cnt; scalar_t__ read_port_complete_EINPROGRESS_cnt; scalar_t__ recvbuf_null_cnt; scalar_t__ recvbuf_skb_alloc_fail_cnt; TYPE_3__ free_recv_queue; int /*<<< orphan*/ * precv_frame_buf; int /*<<< orphan*/ * pallocated_frame_buf; int /*<<< orphan*/ * adapter; TYPE_3__ uc_swdec_pending_queue; TYPE_3__ recv_pending_queue; int /*<<< orphan*/  lock; } ;
typedef  int sint ;
typedef  int /*<<< orphan*/  _adapter ;
typedef  int /*<<< orphan*/  SIZE_PTR ;

/* Variables and functions */
 int NR_RECVFRAME ; 
 scalar_t__ N_BYTE_ALIGMENT (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RXFRAME_ALIGN_SZ ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_init_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  _rtw_spinlock_init (int /*<<< orphan*/ *) ; 
 int rtw_hal_init_recv_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rtw_os_recv_resource_alloc (int /*<<< orphan*/ *,union recv_frame*) ; 
 int /*<<< orphan*/  rtw_os_recv_resource_init (struct recv_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtw_zvmalloc (scalar_t__) ; 

sint _rtw_init_recv_priv(struct recv_priv *precvpriv, _adapter *padapter)
{
	sint i;

	union recv_frame *precvframe;

	sint	res=_SUCCESS;

_func_enter_;

	// We don't need to memset padapter->XXX to zero, because adapter is allocated by rtw_zvmalloc().
	//_rtw_memset((unsigned char *)precvpriv, 0, sizeof (struct  recv_priv));

	_rtw_spinlock_init(&precvpriv->lock);

	_rtw_init_queue(&precvpriv->free_recv_queue);
	_rtw_init_queue(&precvpriv->recv_pending_queue);
	_rtw_init_queue(&precvpriv->uc_swdec_pending_queue);

	precvpriv->adapter = padapter;

	precvpriv->free_recvframe_cnt = NR_RECVFRAME;

	rtw_os_recv_resource_init(precvpriv, padapter);

	precvpriv->pallocated_frame_buf = rtw_zvmalloc(NR_RECVFRAME * sizeof(union recv_frame) + RXFRAME_ALIGN_SZ);
	
	if(precvpriv->pallocated_frame_buf==NULL){
		res= _FAIL;
		goto exit;
	}
	//_rtw_memset(precvpriv->pallocated_frame_buf, 0, NR_RECVFRAME * sizeof(union recv_frame) + RXFRAME_ALIGN_SZ);

	precvpriv->precv_frame_buf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(precvpriv->pallocated_frame_buf), RXFRAME_ALIGN_SZ);
	//precvpriv->precv_frame_buf = precvpriv->pallocated_frame_buf + RXFRAME_ALIGN_SZ -
	//						((SIZE_PTR) (precvpriv->pallocated_frame_buf) &(RXFRAME_ALIGN_SZ-1));

	precvframe = (union recv_frame*) precvpriv->precv_frame_buf;


	for(i=0; i < NR_RECVFRAME ; i++)
	{
		_rtw_init_listhead(&(precvframe->u.list));

		rtw_list_insert_tail(&(precvframe->u.list), &(precvpriv->free_recv_queue.queue));

		res = rtw_os_recv_resource_alloc(padapter, precvframe);

		precvframe->u.hdr.adapter =padapter;
		precvframe++;

	}

#ifdef CONFIG_USB_HCI

	precvpriv->rx_pending_cnt=1;

	_rtw_init_sema(&precvpriv->allrxreturnevt, 0);

#endif

	res = rtw_hal_init_recv_priv(padapter);

	precvpriv->recvbuf_skb_alloc_fail_cnt = 0;
	precvpriv->recvbuf_null_cnt = 0;
	precvpriv->read_port_complete_EINPROGRESS_cnt = 0;
	precvpriv->read_port_complete_other_urb_err_cnt = 0;

#ifdef CONFIG_NEW_SIGNAL_STAT_PROCESS
	#ifdef PLATFORM_LINUX
		#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 15, 0)
			_init_timer(&precvpriv->signal_stat_timer, padapter->pnetdev, RTW_TIMER_HDL_NAME(signal_stat), padapter);
		#else
			timer_setup(&precvpriv->signal_stat_timer, RTW_TIMER_HDL_NAME(signal_stat), 0);
		#endif
	#elif defined(PLATFORM_OS_CE) || defined(PLATFORM_WINDOWS)
	_init_timer(&precvpriv->signal_stat_timer, padapter->hndis_adapter, RTW_TIMER_HDL_NAME(signal_stat), padapter);
	#endif

	precvpriv->signal_stat_sampling_interval = 1000; //ms
	//precvpriv->signal_stat_converging_constant = 5000; //ms

	rtw_set_signal_stat_timer(precvpriv);
#endif //CONFIG_NEW_SIGNAL_STAT_PROCESS

exit:

_func_exit_;

	return res;

}