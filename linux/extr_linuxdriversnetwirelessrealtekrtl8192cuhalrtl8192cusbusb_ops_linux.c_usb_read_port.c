#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct usb_device {int dummy; } ;
struct recv_priv {int /*<<< orphan*/  recvbuf_null_cnt; int /*<<< orphan*/  rx_pending_cnt; int /*<<< orphan*/  recvbuf_skb_alloc_fail_cnt; } ;
struct recv_buf {scalar_t__ reuse; scalar_t__ pbuf; TYPE_3__* purb; TYPE_6__* pskb; void* pend; void* ptail; scalar_t__ pdata; int /*<<< orphan*/  phead; } ;
struct intf_hdl {TYPE_2__* padapter; } ;
struct dvobj_priv {struct usb_device* pusbdev; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_12__ {scalar_t__ pnp_bstop_trx; } ;
struct TYPE_13__ {TYPE_1__ pwrctrlpriv; scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; struct recv_priv recvpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_15__ {scalar_t__ data; int /*<<< orphan*/  head; } ;
struct TYPE_14__ {int /*<<< orphan*/  status; } ;
typedef  int SIZE_PTR ;
typedef  TYPE_3__* PURB ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*,int,int /*<<< orphan*/ ) ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAX_RECVBUF_SZ ; 
 int RECVBUFF_ALIGN_SZ ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FAIL ; 
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 struct dvobj_priv* adapter_to_dvobj (TYPE_2__*) ; 
 unsigned int ffaddr2pipehdl (struct dvobj_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192cu_init_recvbuf (TYPE_2__*,struct recv_buf*) ; 
 TYPE_6__* rtw_skb_alloc (scalar_t__) ; 
 void* skb_end_pointer (TYPE_6__*) ; 
 int /*<<< orphan*/  skb_reserve (TYPE_6__*,int) ; 
 void* skb_tail_pointer (TYPE_6__*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_3__*,struct usb_device*,unsigned int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct recv_buf*) ; 
 int /*<<< orphan*/  usb_read_port_complete ; 
 int usb_submit_urb (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 usb_read_port(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *rmem)
{	
	_irqL irqL;
	int err;
	unsigned int pipe;
	SIZE_PTR tmpaddr=0;
	SIZE_PTR alignment=0;
	u32 ret = _SUCCESS;
	PURB purb = NULL;
	struct recv_buf	*precvbuf = (struct recv_buf *)rmem;
	_adapter		*adapter = pintfhdl->padapter;
	struct dvobj_priv	*pdvobj = adapter_to_dvobj(adapter);
	struct recv_priv	*precvpriv = &adapter->recvpriv;
	struct usb_device	*pusbd = pdvobj->pusbdev;
	
_func_enter_;
	
	if(adapter->bDriverStopped || adapter->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)
	{
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port:( padapter->bDriverStopped ||padapter->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n"));
		return _FAIL;
	}

#ifdef CONFIG_PREALLOC_RECV_SKB
	if((precvbuf->reuse == _FALSE) || (precvbuf->pskb == NULL))
	{
		if (NULL != (precvbuf->pskb = skb_dequeue(&precvpriv->free_recv_skb_queue)))
		{
			precvbuf->reuse = _TRUE;
		}
	}
#endif
	

	if(precvbuf !=NULL)
	{	
		rtl8192cu_init_recvbuf(adapter, precvbuf);		

		//re-assign for linux based on skb
		if((precvbuf->reuse == _FALSE) || (precvbuf->pskb == NULL))
		{
			precvbuf->pskb = rtw_skb_alloc(MAX_RECVBUF_SZ + RECVBUFF_ALIGN_SZ);

			if(precvbuf->pskb == NULL)		
			{
				RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("init_recvbuf(): alloc_skb fail!\n"));
				precvpriv->recvbuf_skb_alloc_fail_cnt++;
				return _FAIL;
			}	

			tmpaddr = (SIZE_PTR)precvbuf->pskb->data;
	        	alignment = tmpaddr & (RECVBUFF_ALIGN_SZ-1);
			skb_reserve(precvbuf->pskb, (RECVBUFF_ALIGN_SZ - alignment));

			precvbuf->phead = precvbuf->pskb->head;
		   	precvbuf->pdata = precvbuf->pskb->data;
			precvbuf->ptail = skb_tail_pointer(precvbuf->pskb);
			precvbuf->pend = skb_end_pointer(precvbuf->pskb);
			precvbuf->pbuf = precvbuf->pskb->data;
		}	
		else//reuse skb
		{
			precvbuf->phead = precvbuf->pskb->head;
			precvbuf->pdata = precvbuf->pskb->data;
			precvbuf->ptail = skb_tail_pointer(precvbuf->pskb);
			precvbuf->pend = skb_end_pointer(precvbuf->pskb);
       		precvbuf->pbuf = precvbuf->pskb->data;

			precvbuf->reuse = _FALSE;
		}

		//_enter_critical(&precvpriv->lock, &irqL);
		//precvpriv->rx_pending_cnt++;
		//precvbuf->irp_pending = _TRUE;
		//_exit_critical(&precvpriv->lock, &irqL);

		precvpriv->rx_pending_cnt++;

		purb = precvbuf->purb;

		//translate DMA FIFO addr to pipehandle
		pipe = ffaddr2pipehdl(pdvobj, addr);

		usb_fill_bulk_urb(purb, pusbd, pipe, 
						precvbuf->pbuf,
                				MAX_RECVBUF_SZ,
                				usb_read_port_complete,
                				precvbuf);//context is precvbuf

		err = usb_submit_urb(purb, GFP_ATOMIC);
		if((err) && (err != (-EPERM)))
		{
			RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("cannot submit rx in-token(err=0x%.8x), URB_STATUS =0x%.8x", err, purb->status));
			DBG_8192C("cannot submit rx in-token(err = 0x%08x),urb_status = %d\n",err,purb->status);
			ret = _FAIL;
		}
	}
	else
	{
		precvpriv->recvbuf_null_cnt++;
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port:precvbuf ==NULL\n"));
		ret = _FAIL;
	}

_func_exit_;

	return ret;
}