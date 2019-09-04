#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct recv_priv {scalar_t__ rx_pending_cnt; int /*<<< orphan*/  ff_hwaddr; int /*<<< orphan*/  allrxreturnevt; int /*<<< orphan*/  lock; } ;
struct recv_buf {scalar_t__ pbuf; int /*<<< orphan*/  transfer_len; TYPE_4__* purb; int /*<<< orphan*/  irp_pending; scalar_t__ adapter; } ;
struct intf_hdl {int dummy; } ;
struct dvobj_priv {int dummy; } ;
struct _URB_BULK_OR_INTERRUPT_TRANSFER {int /*<<< orphan*/  TransferBufferLength; } ;
struct TYPE_13__ {scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; TYPE_1__* pio_queue; int /*<<< orphan*/  dvobjpriv; struct recv_priv recvpriv; } ;
typedef  TYPE_3__ _adapter ;
typedef  int /*<<< orphan*/  USBD_STATUS ;
struct TYPE_12__ {int Status; } ;
struct TYPE_15__ {scalar_t__ Cancel; TYPE_2__ IoStatus; } ;
struct TYPE_14__ {struct _URB_BULK_OR_INTERRUPT_TRANSFER UrbBulkOrInterruptTransfer; } ;
struct TYPE_11__ {struct intf_hdl intf; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_4__* PURB ;
typedef  TYPE_5__* PIRP ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RECVBUF_SZ ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RXDESC_SIZE ; 
 int /*<<< orphan*/  STATUS_MORE_PROCESSING_REQUIRED ; 
#define  STATUS_SUCCESS 128 
 int /*<<< orphan*/  URB_STATUS (TYPE_4__*) ; 
 int /*<<< orphan*/  USBD_HALTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _FALSE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_spinlock_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinunlock_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_up_sema (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recvbuf2recvframe (TYPE_3__*,struct recv_buf*) ; 
 int /*<<< orphan*/  rtw_read_port (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  rxcmd_event_hdl (TYPE_3__*,int*) ; 

NTSTATUS usb_read_port_complete(PDEVICE_OBJECT pUsbDevObj, PIRP pIrp, PVOID context)
{	
	uint isevt, *pbuf;
	struct _URB_BULK_OR_INTERRUPT_TRANSFER	*pbulkurb;
	USBD_STATUS		usbdstatus;	
	struct recv_buf		*precvbuf = (struct recv_buf *)context;	
	_adapter 				*adapter =(_adapter *)precvbuf->adapter;
	struct recv_priv		*precvpriv = &adapter->recvpriv;
	struct dvobj_priv   	*dev = (struct dvobj_priv   *)&adapter->dvobjpriv;
	PURB				purb = precvbuf->purb;
	struct intf_hdl 		*pintfhdl = &adapter->pio_queue->intf;
	
	//RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port_complete!!!\n"));

	usbdstatus = URB_STATUS(purb);
	
	_rtw_spinlock_ex(&precvpriv->lock);
	precvbuf->irp_pending=_FALSE;
	precvpriv->rx_pending_cnt --;
	_rtw_spinunlock_ex(&precvpriv->lock);	
	
	if(precvpriv->rx_pending_cnt== 0) {		
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port_complete: rx_pending_cnt== 0, set allrxreturnevt!\n"));
		_rtw_up_sema(&precvpriv->allrxreturnevt);	
	}


	if( pIrp->Cancel == _TRUE ) {
		
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port_complete: One IRP has been cancelled succesfully\n"));
		return STATUS_MORE_PROCESSING_REQUIRED;
	}
	if(adapter->bSurpriseRemoved) {

		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port_complete:bDriverStopped(%d) OR bSurpriseRemoved(%d)", adapter->bDriverStopped, adapter->bSurpriseRemoved));
		return STATUS_MORE_PROCESSING_REQUIRED;
	}

	switch(pIrp->IoStatus.Status) 
	{
		case STATUS_SUCCESS:
			
			pbulkurb = &(precvbuf->purb)->UrbBulkOrInterruptTransfer;
			if((pbulkurb->TransferBufferLength >(MAX_RECVBUF_SZ)) || (pbulkurb->TransferBufferLength < RXDESC_SIZE) ) 
			{								
				RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n usb_read_port_complete: (pbulkurb->TransferBufferLength > MAX_RECVBUF_SZ) || (pbulkurb->TransferBufferLength < RXDESC_SIZE)\n"));
				rtw_read_port(adapter, precvpriv->ff_hwaddr, 0, (unsigned char *)precvbuf);
			}
			else 
			{	
			       precvbuf->transfer_len = pbulkurb->TransferBufferLength;

				pbuf = (uint*)precvbuf->pbuf;

				if((isevt = *(pbuf+1)&0x1ff) == 0x1ff)
				{								
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
	
			break;
			
		default:
			
			if( !USBD_HALTED(usbdstatus) )
			{				
				RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n usb_read_port_complete():USBD_HALTED(usbdstatus)=%x  (need to handle ) \n",USBD_HALTED(usbdstatus)));				
			
			}
			else 
			{				
				RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n usb_read_port_complete(): USBD_HALTED(usbdstatus)=%x \n\n", USBD_HALTED(usbdstatus)) );
				adapter->bDriverStopped = _TRUE;
				adapter->bSurpriseRemoved = _TRUE;
				RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port_complete(): USBD_HALTED(usbdstatus)=%x \n\n", USBD_HALTED(usbdstatus))) ;
			}

		      break;
			  
	}

	return STATUS_MORE_PROCESSING_REQUIRED;
	
}