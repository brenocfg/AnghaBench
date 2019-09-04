#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
typedef  int u16 ;
struct recv_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_pending_cnt; } ;
struct recv_buf {TYPE_7__* pirp; int /*<<< orphan*/  purb; scalar_t__ pbuf; void* irp_pending; } ;
struct intf_priv {scalar_t__ intf_dev; } ;
struct intf_hdl {struct intf_priv* pintfpriv; } ;
struct dvobj_priv {TYPE_5__* padapter; int /*<<< orphan*/  pnextdevobj; } ;
struct _URB_BULK_OR_INTERRUPT_TRANSFER {int dummy; } ;
struct TYPE_14__ {scalar_t__ pnp_bstop_trx; } ;
struct TYPE_19__ {TYPE_1__ pwrctrlpriv; scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; struct recv_priv recvpriv; } ;
typedef  TYPE_6__ _adapter ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  USBD_STATUS ;
struct TYPE_16__ {int /*<<< orphan*/  IoControlCode; } ;
struct TYPE_15__ {int /*<<< orphan*/  Argument1; } ;
struct TYPE_17__ {TYPE_3__ DeviceIoControl; TYPE_2__ Others; } ;
struct TYPE_21__ {int /*<<< orphan*/  MajorFunction; TYPE_4__ Parameters; } ;
struct TYPE_20__ {void* Cancel; } ;
struct TYPE_18__ {void* bSurpriseRemoved; void* bDriverStopped; } ;
typedef  int /*<<< orphan*/  PURB ;
typedef  TYPE_7__* PIRP ;
typedef  TYPE_8__* PIO_STACK_LOCATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_INTERNAL_USB_SUBMIT_URB ; 
 int /*<<< orphan*/  IRP_MJ_INTERNAL_DEVICE_CONTROL ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,TYPE_7__*) ; 
 TYPE_8__* IoGetNextIrpStackLocation (TYPE_7__*) ; 
 int /*<<< orphan*/  IoSetCompletionRoutine (TYPE_7__*,int /*<<< orphan*/ ,struct recv_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_RECVBUF_SZ ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ STATUS_PENDING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  URB_STATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ USBD_HALTED (int /*<<< orphan*/ ) ; 
 int USBD_SHORT_TRANSFER_OK ; 
 int USBD_TRANSFER_DIRECTION_IN ; 
 int /*<<< orphan*/  UsbBuildInterruptOrBulkTransferRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* _FALSE ; 
 void* _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_spinlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffaddr2pipehdl (struct dvobj_priv*,void*) ; 
 int /*<<< orphan*/  rtl8192cu_init_recvbuf (TYPE_6__*,struct recv_buf*) ; 
 int /*<<< orphan*/  usb_read_port_complete ; 

u32 usb_read_port(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *rmem)
{
	u8 					*pdata;
	u16					size;
	PURB				purb;
	PIRP					pirp;
	PIO_STACK_LOCATION	nextStack;
	NTSTATUS			ntstatus;
	USBD_STATUS		usbdstatus;
	HANDLE				PipeHandle;	
	struct recv_buf		*precvbuf = (struct recv_buf *)rmem;
	struct intf_priv		*pintfpriv = pintfhdl->pintfpriv;
	struct dvobj_priv		*pdev = (struct dvobj_priv   *)pintfpriv->intf_dev;
	_adapter				*adapter = (_adapter *)pdev->padapter;
	struct recv_priv		*precvpriv = &adapter->recvpriv;
	u32					bResult = _FALSE;

_func_enter_;
	
	if(adapter->bDriverStopped || adapter->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx) {
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port:( padapter->bDriverStopped ||padapter->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n"));
		return bResult;
	}

	if(precvbuf !=NULL)
	{

		rtl8192cu_init_recvbuf(adapter, precvbuf);
	
		_rtw_spinlock(&precvpriv->lock);
		precvpriv->rx_pending_cnt++;
		precvbuf->irp_pending = _TRUE;
		_rtw_spinunlock(&precvpriv->lock);

	       pdata = (u8*)precvbuf->pbuf;

		size	 = sizeof( struct _URB_BULK_OR_INTERRUPT_TRANSFER );
		purb = precvbuf->purb;	

		//translate DMA FIFO addr to pipehandle
		PipeHandle = ffaddr2pipehdl(pdev, addr);	
		 
		UsbBuildInterruptOrBulkTransferRequest(
			purb,
			(USHORT)size,
			PipeHandle,
			pdata,
			NULL, 
			MAX_RECVBUF_SZ,
			USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK, 
			NULL
			);

		pirp = precvbuf->pirp;

#if NDIS51_MINIPORT
		IoReuseIrp(pirp, STATUS_SUCCESS);
#else
		pirp->Cancel = _FALSE;
#endif

		// call the class driver to perform the operation
		// and pass the URB to the USB driver stack
		nextStack = IoGetNextIrpStackLocation(pirp);
		nextStack->Parameters.Others.Argument1 = purb;
		nextStack->Parameters.DeviceIoControl.IoControlCode = IOCTL_INTERNAL_USB_SUBMIT_URB;
		nextStack->MajorFunction = IRP_MJ_INTERNAL_DEVICE_CONTROL;

		IoSetCompletionRoutine(
			pirp,					// irp to use
			usb_read_port_complete,	// routine to call when irp is done
			precvbuf,					// context to pass routine 
			TRUE,					// call on success
			TRUE,					// call on error
			TRUE);					// call on cancel

		//
		// The IoCallDriver routine  
		// sends an IRP to the driver associated with a specified device object.
		//
		ntstatus = IoCallDriver(pdev->pnextdevobj, pirp);
		usbdstatus = URB_STATUS(purb);

		if( USBD_HALTED(usbdstatus) ) {
			RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n usb_read_port(): USBD_HALTED(usbdstatus=0x%.8x)=%.8x  \n\n", usbdstatus, USBD_HALTED(usbdstatus)));
			pdev->padapter->bDriverStopped=_TRUE;
			pdev->padapter->bSurpriseRemoved=_TRUE;
		}

		if( ntstatus == STATUS_PENDING )
		{ 
			bResult = _TRUE;// The IRP is pended in USBD as we expected.
		}
		else {
			RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port(): IoCallDriver failed!!! IRP STATUS: %X\n", ntstatus));
			RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port(): IoCallDriver failed!!! USB STATUS: %X\n", usbdstatus));
		}

	}
	else{
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port:precv_frame ==NULL\n"));
	}

_func_exit_;
	
	return bResult;
	
}