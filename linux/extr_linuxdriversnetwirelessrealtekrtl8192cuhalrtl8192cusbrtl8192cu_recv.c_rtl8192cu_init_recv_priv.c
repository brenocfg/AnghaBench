#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct recv_priv {int free_recv_buf_queue_cnt; int /*<<< orphan*/ * precv_buf; int /*<<< orphan*/ * pallocated_recv_buf; int /*<<< orphan*/  free_recv_buf_queue; } ;
struct recv_buf {TYPE_1__* adapter; scalar_t__ ref_cnt; int /*<<< orphan*/  alloc_sz; int /*<<< orphan*/  recvbuf_lock; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {struct recv_priv recvpriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  int /*<<< orphan*/  SIZE_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RECVBUF_SZ ; 
 int NR_RECVBUFF ; 
 scalar_t__ N_BYTE_ALIGMENT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_init_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _rtw_spinlock_init (int /*<<< orphan*/ *) ; 
 int rtw_os_recvbuf_resource_alloc (TYPE_1__*,struct recv_buf*) ; 
 int /*<<< orphan*/ * rtw_zmalloc (int) ; 

int	rtl8192cu_init_recv_priv(_adapter *padapter)
{
	struct recv_priv	*precvpriv = &padapter->recvpriv;
	int	i, res = _SUCCESS;
	struct recv_buf *precvbuf;

#ifdef CONFIG_RECV_THREAD_MODE	
	_rtw_init_sema(&precvpriv->recv_sema, 0);//will be removed
	_rtw_init_sema(&precvpriv->terminate_recvthread_sema, 0);//will be removed
#endif

#ifdef PLATFORM_LINUX
	tasklet_init(&precvpriv->recv_tasklet,
	     (void(*)(unsigned long))rtl8192cu_recv_tasklet,
	     (unsigned long)padapter);
#endif

#ifdef CONFIG_USB_INTERRUPT_IN_PIPE
#ifdef PLATFORM_LINUX
	precvpriv->int_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	if(precvpriv->int_in_urb == NULL){
		DBG_8192C("alloc_urb for interrupt in endpoint fail !!!!\n");
	}
#endif
	precvpriv->int_in_buf = rtw_zmalloc(sizeof(INTERRUPT_MSG_FORMAT_EX));
	if(precvpriv->int_in_buf == NULL){
		DBG_8192C("alloc_mem for interrupt in endpoint fail !!!!\n");
	}
#endif

	//init recv_buf
	_rtw_init_queue(&precvpriv->free_recv_buf_queue);

#ifdef CONFIG_USE_USB_BUFFER_ALLOC_RX
	_rtw_init_queue(&precvpriv->recv_buf_pending_queue);
#endif	// CONFIG_USE_USB_BUFFER_ALLOC_RX

	precvpriv->pallocated_recv_buf = rtw_zmalloc(NR_RECVBUFF *sizeof(struct recv_buf) + 4);
	if(precvpriv->pallocated_recv_buf==NULL){
		res= _FAIL;
		RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("alloc recv_buf fail!\n"));
		goto exit;
	}
	_rtw_memset(precvpriv->pallocated_recv_buf, 0, NR_RECVBUFF *sizeof(struct recv_buf) + 4);

	precvpriv->precv_buf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(precvpriv->pallocated_recv_buf), 4);
	//precvpriv->precv_buf = precvpriv->pallocated_recv_buf + 4 -
	//						((uint) (precvpriv->pallocated_recv_buf) &(4-1));


	precvbuf = (struct recv_buf*)precvpriv->precv_buf;

	for(i=0; i < NR_RECVBUFF ; i++)
	{
		_rtw_init_listhead(&precvbuf->list);

		_rtw_spinlock_init(&precvbuf->recvbuf_lock);

		precvbuf->alloc_sz = MAX_RECVBUF_SZ;

		res = rtw_os_recvbuf_resource_alloc(padapter, precvbuf);
		if(res==_FAIL)
			break;

		precvbuf->ref_cnt = 0;
		precvbuf->adapter =padapter;


		//rtw_list_insert_tail(&precvbuf->list, &(precvpriv->free_recv_buf_queue.queue));

		precvbuf++;

	}

	precvpriv->free_recv_buf_queue_cnt = NR_RECVBUFF;

#ifdef PLATFORM_LINUX

	skb_queue_head_init(&precvpriv->rx_skb_queue);

#ifdef CONFIG_PREALLOC_RECV_SKB
	{
		int i;
		SIZE_PTR tmpaddr=0;
		SIZE_PTR alignment=0;
		struct sk_buff *pskb=NULL;

		skb_queue_head_init(&precvpriv->free_recv_skb_queue);

		for(i=0; i<NR_PREALLOC_RECV_SKB; i++)
		{
			pskb = rtw_skb_alloc(MAX_RECVBUF_SZ + RECVBUFF_ALIGN_SZ);

			if(pskb)
			{
				pskb->dev = padapter->pnetdev;

				tmpaddr = (SIZE_PTR)pskb->data;
				alignment = tmpaddr & (RECVBUFF_ALIGN_SZ-1);
				skb_reserve(pskb, (RECVBUFF_ALIGN_SZ - alignment));

				skb_queue_tail(&precvpriv->free_recv_skb_queue, pskb);
			}

			pskb=NULL;

		}
	}
#endif

#endif

exit:

	return res;

}