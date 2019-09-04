#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct zero_bulkout_context {unsigned char* pbuf; TYPE_5__* padapter; int /*<<< orphan*/ * pirp; void* purb; } ;
struct intf_hdl {scalar_t__ adapter; } ;
struct dvobj_priv {int /*<<< orphan*/  pnextdevobj; scalar_t__ nextdevstacksz; } ;
struct _URB_BULK_OR_INTERRUPT_TRANSFER {int dummy; } ;
struct TYPE_8__ {scalar_t__ pnp_bstop_trx; } ;
struct TYPE_12__ {void* bSurpriseRemoved; void* bDriverStopped; TYPE_1__ pwrctrlpriv; int /*<<< orphan*/  dvobjpriv; } ;
typedef  TYPE_5__ _adapter ;
typedef  int /*<<< orphan*/  USBD_STATUS ;
typedef  int /*<<< orphan*/  URB ;
struct TYPE_10__ {int /*<<< orphan*/  IoControlCode; } ;
struct TYPE_9__ {void* Argument1; } ;
struct TYPE_11__ {TYPE_3__ DeviceIoControl; TYPE_2__ Others; } ;
struct TYPE_13__ {TYPE_4__ Parameters; int /*<<< orphan*/  MajorFunction; } ;
typedef  void* PURB ;
typedef  int /*<<< orphan*/ * PIRP ;
typedef  TYPE_6__* PIO_STACK_LOCATION ;
typedef  scalar_t__ NDIS_STATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IOCTL_INTERNAL_USB_SUBMIT_URB ; 
 int /*<<< orphan*/  IRP_MJ_INTERNAL_DEVICE_CONTROL ; 
 int /*<<< orphan*/ * IoAllocateIrp (char,int /*<<< orphan*/ ) ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* IoGetNextIrpStackLocation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoSetCompletionRoutine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct zero_bulkout_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  NonPagedPool ; 
 scalar_t__ STATUS_PENDING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  URB_STATUS (void*) ; 
 scalar_t__ USBD_HALTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UsbBuildInterruptOrBulkTransferRequest (void*,int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 void* _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  ffaddr2pipehdl (struct dvobj_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_bulkout_zero_complete ; 

u32 usb_bulkout_zero(struct intf_hdl *pintfhdl, u32 addr)
{	
	struct zero_bulkout_context *pcontext;
	unsigned char *pbuf;
	char NextDeviceStackSize, len;
	PIO_STACK_LOCATION	nextStack;
	USBD_STATUS		usbdstatus;
	HANDLE				PipeHandle;	
	PIRP					pirp = NULL;
	PURB				purb = NULL;	
	NDIS_STATUS			ndisStatus = NDIS_STATUS_SUCCESS;
	_adapter *padapter = (_adapter *)pintfhdl->adapter;
	struct dvobj_priv	*pdvobj = (struct dvobj_priv *)&padapter->dvobjpriv;	


_func_enter_;

	if((padapter->bDriverStopped) || (padapter->bSurpriseRemoved) ||(padapter->pwrctrlpriv.pnp_bstop_trx))
	{		
		return _FAIL;
	}

	len = 0;
	NextDeviceStackSize = (char)pdvobj->nextdevstacksz;

	pcontext = (struct zero_bulkout_context *)ExAllocatePool(NonPagedPool, sizeof(struct zero_bulkout_context));
	pbuf = (unsigned char *)ExAllocatePool(NonPagedPool, sizeof(int));	
    	purb = (PURB)ExAllocatePool(NonPagedPool, sizeof(URB));
      	pirp = IoAllocateIrp(NextDeviceStackSize, FALSE);

	pcontext->pbuf = pbuf;
	pcontext->purb = purb;
	pcontext->pirp = pirp;
	pcontext->padapter = padapter;
                    
	//translate DMA FIFO addr to pipehandle
	PipeHandle = ffaddr2pipehdl(pdvobj, addr);	


	// Build our URB for USBD
	UsbBuildInterruptOrBulkTransferRequest(
				purb,
				sizeof(struct _URB_BULK_OR_INTERRUPT_TRANSFER),
				PipeHandle,
				pbuf, 
				NULL, 
				len, 
				0, 
				NULL);
	
	//
	// call the calss driver to perform the operation
	// pass the URB to the USB driver stack
	//
	nextStack = IoGetNextIrpStackLocation(pirp);
	nextStack->MajorFunction = IRP_MJ_INTERNAL_DEVICE_CONTROL;
	nextStack->Parameters.Others.Argument1 = purb;
	nextStack->Parameters.DeviceIoControl.IoControlCode = IOCTL_INTERNAL_USB_SUBMIT_URB;

	//Set Completion Routine
	IoSetCompletionRoutine(pirp,					// irp to use
				               usb_bulkout_zero_complete,	// callback routine
				               pcontext,				// context 
				               TRUE,					// call on success
				               TRUE,					// call on error
				               TRUE);					// call on cancel

	
	// Call IoCallDriver to send the irp to the usb bus driver
	//
	ndisStatus = IoCallDriver(pdvobj->pnextdevobj, pirp);
	usbdstatus = URB_STATUS(purb);

	if( USBD_HALTED(usbdstatus) )
	{		
		padapter->bDriverStopped=_TRUE;
		padapter->bSurpriseRemoved=_TRUE;
	}

	//
	// The usb bus driver should always return STATUS_PENDING when bulk out irp async
	//
	if ( ndisStatus != STATUS_PENDING )
	{		
		return _FAIL;
	} 	
	
_func_exit_;
	
	return _SUCCESS;

}