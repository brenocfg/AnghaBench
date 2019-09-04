#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xmit_priv {int dummy; } ;
struct io_req {int /*<<< orphan*/  sema; int /*<<< orphan*/  usb_transfer_write_mem; int /*<<< orphan*/  list; } ;
struct io_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  processing; } ;
struct intf_priv {scalar_t__ intf_dev; } ;
struct intf_hdl {struct intf_priv* pintfpriv; scalar_t__ adapter; } ;
struct TYPE_5__ {TYPE_4__* _lpUsbFuncs; } ;
struct dvobj_priv {TYPE_1__ usb_extension; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_6__ {scalar_t__ pnp_bstop_trx; } ;
struct TYPE_7__ {TYPE_2__ pwrctrlpriv; scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; scalar_t__ pio_queue; struct xmit_priv xmitpriv; } ;
typedef  TYPE_3__ _adapter ;
typedef  int /*<<< orphan*/  USB_PIPE ;
struct TYPE_8__ {int /*<<< orphan*/  (* lpIssueBulkTransfer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct io_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_4__* LPCUSB_FUNCS ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  USB_CANCELED_ERROR ; 
 int /*<<< orphan*/  USB_OUT_TRANSFER ; 
 int _FALSE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_down_sema (int /*<<< orphan*/ *) ; 
 struct io_req* alloc_ioreq (struct io_queue*) ; 
 int /*<<< orphan*/  ffaddr2pipehdl (struct dvobj_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_ioreq (struct io_req*,struct io_queue*) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct io_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write_mem_complete ; 

void usb_write_mem(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *wmem)
{

	NTSTATUS NtStatus = STATUS_SUCCESS;
    USB_PIPE	hPipe;
	_irqL	irqL;

	int 	fComplete	= _FALSE;
	DWORD	dwBytes 	= 0;
	DWORD	dwErr		= USB_CANCELED_ERROR;


	struct io_req 		*pio_req;

	_adapter 			*adapter 	= (_adapter *)pintfhdl->adapter;
	struct intf_priv 	*pintfpriv	= pintfhdl->pintfpriv;
	struct dvobj_priv   * pdvobj_priv   = (struct dvobj_priv*)pintfpriv->intf_dev;

	 
    struct xmit_priv	*pxmitpriv	= &adapter->xmitpriv;
	struct io_queue 	*pio_queue 	= (struct io_queue *)adapter->pio_queue; 

	LPCUSB_FUNCS usb_funcs_vp = pdvobj_priv->usb_extension._lpUsbFuncs;


_func_enter_;
	RT_TRACE( _module_hci_ops_os_c_, _drv_info_, ("usb_write_mem(%u) pintfhdl %p wmem %p\n", __LINE__, pintfhdl, wmem));

	// fetch a io_request from the io_queue
	pio_req = alloc_ioreq(pio_queue);
		
	if ((pio_req == NULL)||(adapter->bSurpriseRemoved))
	{
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("async_irp_write32 : pio_req =0x%x adapter->bSurpriseRemoved=0x%x",pio_req,adapter->bSurpriseRemoved ));
		goto exit;
	}	

	_enter_critical_bh(&(pio_queue->lock), &irqL);


	// insert the io_request into processing io_queue
	rtw_list_insert_tail(&(pio_req->list),&(pio_queue->processing));
	
	
	if((adapter->bDriverStopped) || (adapter->bSurpriseRemoved) ||(adapter->pwrctrlpriv.pnp_bstop_trx)) 
	{
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\npadapter->pwrctrlpriv.pnp_bstop_trx==_TRUE\n"));
		goto exit;
	}
	
	//translate DMA FIFO addr to pipehandle
	hPipe = ffaddr2pipehdl(pdvobj_priv, addr);	

	RT_TRACE( _module_hci_ops_os_c_, _drv_info_,("usb_write_mem(%u)\n",__LINE__));

	pio_req->usb_transfer_write_mem = (*usb_funcs_vp->lpIssueBulkTransfer)(
		hPipe,
		usb_write_mem_complete, 
		pio_queue,
		USB_OUT_TRANSFER,
		cnt,
		wmem,
		0);

#if 0

	(*usb_funcs_vp->lpGetTransferStatus)(pio_req->usb_transfer_write_mem , &dwBytes, &dwErr);

	while( fComplete != _TRUE)
	{
		fComplete = (*usb_funcs_vp->lpIsTransferComplete)(pio_req->usb_transfer_write_mem);
		if(fComplete==_TRUE)
		{
			(*usb_funcs_vp->lpCloseTransfer)(pio_req->usb_transfer_write_mem );
			RT_TRACE( _module_hci_ops_os_c_, _drv_err_, ("usb_write_mem finished\n"));
			break;
		}
		else
		{
			RT_TRACE( _module_hci_ops_os_c_, _drv_err_, 
				("usb_write_mem not yet finished %X\n", 
				pio_req->usb_transfer_write_mem));
			rtw_msleep_os(10);
		}
		
	}

#endif


//	_rtw_down_sema(&pio_req->sema);	

	RT_TRACE( _module_hci_ops_os_c_, _drv_info_, ("-usb_write_mem(%X)\n",pio_req->usb_transfer_write_mem));

	_exit_critical_bh(&(pio_queue->lock), &irqL);

	_rtw_down_sema(&pio_req->sema); 
	free_ioreq(pio_req, pio_queue);

exit:
_func_exit_;
	return;
}