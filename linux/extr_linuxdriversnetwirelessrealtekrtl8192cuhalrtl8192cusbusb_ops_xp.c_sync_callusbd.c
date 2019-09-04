#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dvobj_priv {int /*<<< orphan*/  pphysdevobj; int /*<<< orphan*/ * padapter; } ;
typedef  int /*<<< orphan*/  _adapter ;
typedef  int /*<<< orphan*/  USBD_STATUS ;
struct TYPE_10__ {int QuadPart; } ;
struct TYPE_7__ {int /*<<< orphan*/  Argument1; } ;
struct TYPE_8__ {TYPE_1__ Others; } ;
struct TYPE_9__ {TYPE_2__ Parameters; } ;
typedef  int /*<<< orphan*/  PURB ;
typedef  int /*<<< orphan*/ * PIRP ;
typedef  TYPE_3__* PIO_STACK_LOCATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_4__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  KEVENT ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  IOCTL_INTERNAL_USB_SUBMIT_URB ; 
 int /*<<< orphan*/ * IoBuildDeviceIoControlRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoCancelIrp (int /*<<< orphan*/ *) ; 
 TYPE_3__* IoGetNextIrpStackLocation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ STATUS_TIMEOUT ; 
 int /*<<< orphan*/  URB_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_STATUS_SUCCESS ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 

NTSTATUS  sync_callusbd(struct dvobj_priv *pdvobjpriv, PURB purb)
{

	KEVENT					kevent;
	PIRP						irp;
	IO_STATUS_BLOCK		iostatusblock;
	PIO_STACK_LOCATION		nextstack;
	USBD_STATUS			usbdstatus;
	LARGE_INTEGER			waittime;
	NTSTATUS ntstatus = STATUS_SUCCESS;
	_adapter *padapter = pdvobjpriv->padapter;
	

	_func_enter_;

//	if(padapter->bDriverStopped) {
//		goto exit;
//	}
	
	KeInitializeEvent(&kevent, NotificationEvent, _FALSE);
	irp = IoBuildDeviceIoControlRequest(
			IOCTL_INTERNAL_USB_SUBMIT_URB,
			pdvobjpriv->pphysdevobj,//CEdevice->pUsbDevObj, 
			NULL, 
			0, 
			NULL, 
			0, 
			_TRUE, 
			&kevent, 
			&iostatusblock);

	if(irp == NULL) {
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("SyncCallUSBD: memory alloc for irp failed\n"));
		ntstatus=STATUS_INSUFFICIENT_RESOURCES;
		goto exit;
	}
	
	nextstack = IoGetNextIrpStackLocation(irp);
	if(nextstack == NULL)	
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("IoGetNextIrpStackLocation fail\n"));

	nextstack->Parameters.Others.Argument1 = purb;
	
	// Issue an IRP for Sync IO.
	ntstatus = IoCallDriver(pdvobjpriv->pphysdevobj, irp);
	usbdstatus = URB_STATUS(purb);

	if(ntstatus == STATUS_PENDING)
	{		
		// Method 1
		waittime.QuadPart = -10000 * 50000;
		ntstatus = KeWaitForSingleObject(&kevent, Executive, KernelMode, _FALSE, &waittime); //8150 code
		
		// Method 2
		//ntStatus = KeWaitForSingleObject(&Kevent, Executive, KernelMode, FALSE, NULL); //DDK sample
		
		usbdstatus = URB_STATUS(purb);

		if(ntstatus == STATUS_TIMEOUT) 
		{			
			//usbdevice->nIoStuckCnt++;
			RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("SyncCallUSBD: TIMEOUT....5000ms\n"));

			// Method 2
			IoCancelIrp(irp);
			ntstatus = KeWaitForSingleObject(&kevent, Executive, KernelMode, _FALSE, NULL); //DDK sample
			usbdstatus = URB_STATUS(purb);

			usbdstatus = USBD_STATUS_SUCCESS;
		}
		
	}
	
exit:	
	
	_func_exit_;
	
	return ntstatus;
	
}