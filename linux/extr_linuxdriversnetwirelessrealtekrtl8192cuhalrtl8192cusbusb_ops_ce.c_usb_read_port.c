#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct recv_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_pending_cnt; } ;
struct recv_buf {scalar_t__ usb_transfer_read_port; int /*<<< orphan*/  pbuf; int /*<<< orphan*/  irp_pending; } ;
struct intf_priv {scalar_t__ intf_dev; } ;
struct intf_hdl {struct intf_priv* pintfpriv; } ;
struct TYPE_5__ {TYPE_3__* _lpUsbFuncs; } ;
struct dvobj_priv {TYPE_1__ usb_extension; scalar_t__ padapter; } ;
struct TYPE_6__ {scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; struct recv_priv recvpriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  int /*<<< orphan*/ * USB_TRANSFER ;
typedef  int /*<<< orphan*/  USB_PIPE ;
struct TYPE_7__ {scalar_t__ (* lpIssueBulkTransfer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct recv_buf*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__* LPCUSB_FUNCS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MAX_RECVBUF_SZ ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int USB_IN_TRANSFER ; 
 int USB_SHORT_TRANSFER_OK ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_spinlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffaddr2pipehdl (struct dvobj_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192cu_init_recvbuf (TYPE_2__*,struct recv_buf*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct recv_buf*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_read_port_complete ; 

u32 usb_read_port(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *rmem)
{
    struct intf_priv	*pintfpriv		= pintfhdl->pintfpriv;
    struct dvobj_priv	*pdvobj_priv	= (struct dvobj_priv*)pintfpriv->intf_dev;
    _adapter			*adapter		= (_adapter *)pdvobj_priv->padapter;

	struct recv_priv	*precvpriv	= &adapter->recvpriv;

	struct recv_buf		*precvbuf	= (struct recv_buf *)rmem;
	DWORD dwErr = ERROR_SUCCESS ;
	DWORD dwBytesTransferred = 0 ;
	USB_TRANSFER hTransfer = NULL;
	USB_PIPE	hPipe;
	LPCUSB_FUNCS usb_funcs_vp = pdvobj_priv->usb_extension._lpUsbFuncs;

_func_enter_;
	RT_TRACE( _module_hci_ops_os_c_, _drv_info_, ("usb_read_port(%u)\n", __LINE__));

#if (CONFIG_PWRCTRL == 1)
    if (adapter->pwrctrlpriv.pnp_bstop_trx)
	{
        return _FALSE;
    }
#endif

	if(adapter->bDriverStopped || adapter->bSurpriseRemoved) 
	{
		RT_TRACE(_module_hci_ops_os_c_, _drv_info_,("usb_read_port:( padapter->bDriverStopped ||padapter->bSurpriseRemoved)!!!\n"));
		return _FALSE;
	}

	if(precvbuf !=NULL)
	{

		// get a recv buffer
		rtl8192cu_init_recvbuf(adapter, precvbuf);
	


		_rtw_spinlock(&precvpriv->lock);
		precvpriv->rx_pending_cnt++;
		precvbuf->irp_pending = _TRUE;
		_rtw_spinunlock(&precvpriv->lock);


		//translate DMA FIFO addr to pipehandle
		hPipe = ffaddr2pipehdl(pdvobj_priv, addr);
		

		RT_TRACE( _module_hci_ops_os_c_, _drv_info_, ("usb_read_port(%u)\n", __LINE__));

		precvbuf->usb_transfer_read_port = (*usb_funcs_vp->lpIssueBulkTransfer)(
			hPipe,
			usb_read_port_complete,
			precvbuf,
			USB_IN_TRANSFER|USB_SHORT_TRANSFER_OK,
			MAX_RECVBUF_SZ,
			precvbuf->pbuf,
			0);


		if(precvbuf->usb_transfer_read_port)
		{
			
		//	  GetTransferStatus(usb_funcs_vp, hTransfer, &dwBytesTransferred,&UsbRc);

		//	  CloseTransferHandle(usb_funcs_vp, hTransfer);

		}
		else
		{

			dwErr = GetLastError();
			//RT_TRACE( _module_hci_ops_os_c_, _drv_err_, ("usb_read_port ERROR : %d\n", dwErr));		 

		}

//	 	if (  USB_NO_ERROR != UsbRc && ERROR_SUCCESS == dwErr) {
//	        dwErr = ERROR_GEN_FAILURE;
//	    }


		if ( ERROR_SUCCESS != dwErr ) {

			SetLastError(dwErr);
			RT_TRACE( _module_hci_ops_os_c_, _drv_err_, ("usb_read_port ERROR : %d\n", dwErr));	
		}
	
		RT_TRACE( _module_hci_ops_os_c_, _drv_info_, ("-usb_read_port(%u)\n", __LINE__));

	}
	else // if(precvbuf !=NULL)
	{
		
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port:precv_frame ==NULL\n"));
	}

	return _TRUE;

}