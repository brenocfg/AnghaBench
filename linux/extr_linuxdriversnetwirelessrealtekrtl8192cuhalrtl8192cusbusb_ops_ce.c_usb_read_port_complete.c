#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct recv_priv {int /*<<< orphan*/  ff_hwaddr; int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_pending_cnt; } ;
struct recv_buf {scalar_t__ pbuf; scalar_t__ transfer_len; int /*<<< orphan*/  usb_transfer_read_port; void* irp_pending; scalar_t__ adapter; } ;
struct intf_priv {scalar_t__ intf_dev; } ;
struct intf_hdl {struct intf_priv* pintfpriv; } ;
struct TYPE_9__ {TYPE_4__* _lpUsbFuncs; } ;
struct dvobj_priv {TYPE_2__ usb_extension; } ;
struct TYPE_10__ {TYPE_1__* pio_queue; struct recv_priv recvpriv; } ;
typedef  TYPE_3__ _adapter ;
struct TYPE_11__ {int (* lpIsTransferComplete ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lpCloseTransfer ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lpGetTransferStatus ) (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ;} ;
struct TYPE_8__ {struct intf_hdl intf; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_4__* LPCUSB_FUNCS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MAX_RECVBUF_SZ ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RXDESC_SIZE ; 
 scalar_t__ USB_CANCELED_ERROR ; 
 scalar_t__ USB_NO_ERROR ; 
 scalar_t__ _FAIL ; 
 void* _FALSE ; 
 int _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_spinlock_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinunlock_ex (int /*<<< orphan*/ *) ; 
 scalar_t__ recvbuf2recvframe (TYPE_3__*,struct recv_buf*) ; 
 int /*<<< orphan*/  rtw_read_port (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  rxcmd_event_hdl (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

DWORD usb_read_port_complete( PVOID context )
{
	struct recv_buf 	*precvbuf	= (struct recv_buf *)context;
	_adapter			*adapter	= (_adapter *)precvbuf->adapter;
	struct recv_priv	*precvpriv	= &adapter->recvpriv;


	struct intf_hdl		*pintfhdl = &adapter->pio_queue->intf;
    struct intf_priv	*pintfpriv    = pintfhdl->pintfpriv;
    struct dvobj_priv	*pdvobj_priv  = (struct dvobj_priv*)pintfpriv->intf_dev;


	LPCUSB_FUNCS usb_funcs_vp = pdvobj_priv->usb_extension._lpUsbFuncs;

    DWORD dwBytesTransferred    = 0;
    DWORD dwErr                 = USB_CANCELED_ERROR;

	uint isevt, *pbuf;
	int fComplete =_FALSE;


	RT_TRACE( _module_hci_ops_os_c_, _drv_info_, ("usb_read_port_complete(%u)\n", __LINE__));

_func_enter_;


	_rtw_spinlock_ex(&precvpriv->lock);
	precvbuf->irp_pending=_FALSE;
	precvpriv->rx_pending_cnt --;
	_rtw_spinunlock_ex(&precvpriv->lock);	


#if 1
		
	(*usb_funcs_vp->lpGetTransferStatus)(precvbuf->usb_transfer_read_port, &dwBytesTransferred, &dwErr);
	fComplete = (*usb_funcs_vp->lpIsTransferComplete)(precvbuf->usb_transfer_read_port);
	if(fComplete!=_TRUE)
	{
		RT_TRACE( _module_hci_ops_os_c_, _drv_err_, ("usb_read_port_complete CloseTransfer before complete\n"));
	}
	(*usb_funcs_vp->lpCloseTransfer)(precvbuf->usb_transfer_read_port);
	
	
#endif


	if(USB_NO_ERROR != dwErr)
		RT_TRACE( _module_hci_ops_os_c_, _drv_err_, ("usb_read_port_complete Fail :%d\n",dwErr));
	
	{

		if ( dwBytesTransferred > MAX_RECVBUF_SZ || dwBytesTransferred < RXDESC_SIZE )
		{
			RT_TRACE(_module_hci_ops_os_c_,_drv_err_,
				("\n usb_read_port_complete: (pbulkurb->TransferBufferLength > MAX_RECVBUF_SZ) || (pbulkurb->TransferBufferLength < RXDESC_SIZE): %d\n",dwBytesTransferred));
			rtw_read_port(adapter, precvpriv->ff_hwaddr, 0, (unsigned char *)precvbuf);

    	    //usb_read_port(pintfhdl, 0, 0, (unsigned char *)precvframe);
    	}
		else
		{
			precvbuf->transfer_len = dwBytesTransferred;

			pbuf = (uint*)precvbuf->pbuf;

			if((isevt = *(pbuf+1)&0x1ff) == 0x1ff)
			{
				RT_TRACE(_module_hci_ops_os_c_,_drv_info_,
					("\n usb_read_port_complete: get a event\n"));
				rxcmd_event_hdl(adapter, pbuf);//rx c2h events

				rtw_read_port(adapter, precvpriv->ff_hwaddr, 0, (unsigned char *)precvbuf);
			}
			else
			{
				if(recvbuf2recvframe(adapter, precvbuf)==_FAIL)//rx packets
				{
					//precvbuf->reuse = _TRUE;		
					rtw_read_port(adapter, precvpriv->ff_hwaddr, 0, (unsigned char *)precvbuf);
				}
			}
	    }
	}

	RT_TRACE( _module_hci_ops_os_c_, _drv_info_, ("-usb_read_port_complete(%u)\n", __LINE__));

_func_exit_;
	return ERROR_SUCCESS;
//	return STATUS_MORE_PROCESSING_REQUIRED;
}