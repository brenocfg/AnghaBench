#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct io_req {int /*<<< orphan*/  sema; int /*<<< orphan*/  list; } ;
struct io_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  processing; } ;
struct intf_priv {int bio_irp_pending; int /*<<< orphan*/  io_irp_cnt; TYPE_6__* piorw_irp; scalar_t__ piorw_urb; scalar_t__ intf_dev; } ;
struct intf_hdl {struct intf_priv* pintfpriv; scalar_t__ adapter; } ;
struct dvobj_priv {scalar_t__ ishighspeed; int /*<<< orphan*/  pnextdevobj; } ;
struct _URB_BULK_OR_INTERRUPT_TRANSFER {int dummy; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_12__ {scalar_t__ pnp_bstop_trx; } ;
struct TYPE_16__ {TYPE_1__ pwrctrlpriv; scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; scalar_t__ pio_queue; } ;
typedef  TYPE_5__ _adapter ;
typedef  int /*<<< orphan*/  USBD_STATUS ;
struct TYPE_14__ {int /*<<< orphan*/  IoControlCode; } ;
struct TYPE_13__ {scalar_t__ Argument1; } ;
struct TYPE_15__ {TYPE_3__ DeviceIoControl; TYPE_2__ Others; } ;
struct TYPE_18__ {TYPE_4__ Parameters; int /*<<< orphan*/  MajorFunction; } ;
struct TYPE_17__ {void* Cancel; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ PURB ;
typedef  TYPE_6__* PIRP ;
typedef  TYPE_7__* PIO_STACK_LOCATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_INTERNAL_USB_SUBMIT_URB ; 
 int /*<<< orphan*/  IRP_MJ_INTERNAL_DEVICE_CONTROL ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_7__* IoGetNextIrpStackLocation (TYPE_6__*) ; 
 int /*<<< orphan*/  IoSetCompletionRoutine (TYPE_6__*,int /*<<< orphan*/ ,struct io_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  URB_STATUS (scalar_t__) ; 
 scalar_t__ USBD_HALTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UsbBuildInterruptOrBulkTransferRequest (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* _FALSE ; 
 int _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_down_sema (int /*<<< orphan*/ *) ; 
 struct io_req* alloc_ioreq (struct io_queue*) ; 
 int /*<<< orphan*/  ffaddr2pipehdl (struct dvobj_priv*,int) ; 
 int /*<<< orphan*/  free_ioreq (struct io_req*,struct io_queue*) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_bulkout_zero (struct intf_hdl*,int) ; 
 int /*<<< orphan*/  usb_write_mem_complete ; 

void usb_write_mem(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *wmem)
{
	u32 bwritezero;
	_irqL	irqL;
	USBD_STATUS			usbdstatus;		
	PIO_STACK_LOCATION		nextStack;
	HANDLE				PipeHandle;	
	struct io_req *pio_req;
	
	_adapter *adapter = (_adapter *)pintfhdl->adapter;
	struct intf_priv *pintfpriv = pintfhdl->pintfpriv;
	struct dvobj_priv   *pdev = (struct dvobj_priv   *)pintfpriv->intf_dev;      
	PURB	piorw_urb = pintfpriv->piorw_urb;
	PIRP		piorw_irp  = pintfpriv->piorw_irp; 	
	struct io_queue	*pio_queue = (struct io_queue *)adapter->pio_queue;	
	NTSTATUS NtStatus = STATUS_SUCCESS;	
	
	_func_enter_;	

	pio_req = alloc_ioreq(pio_queue);
	
	if ((pio_req == NULL)||(adapter->bSurpriseRemoved)){
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("async_irp_write32 : pio_req =0x%x adapter->bSurpriseRemoved=0x%x",pio_req,adapter->bSurpriseRemoved ));
		goto exit;
	}	
	
	_enter_critical_bh(&(pio_queue->lock), &irqL);
	
	rtw_list_insert_tail(&(pio_req->list),&(pio_queue->processing));


#ifdef NDIS51_MINIPORT
	IoReuseIrp(piorw_irp, STATUS_SUCCESS);
#else
	piorw_irp->Cancel = _FALSE;
#endif

	if((adapter->bDriverStopped) || (adapter->bSurpriseRemoved) ||(adapter->pwrctrlpriv.pnp_bstop_trx))	
	{
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\npadapter->pwrctrlpriv.pnp_bstop_trx==_TRUE\n"));
		_func_exit_;
		return;
	}

	//translate DMA FIFO addr to pipehandle
	PipeHandle = ffaddr2pipehdl(pdev, addr);	

	
	pintfpriv->io_irp_cnt++;
	pintfpriv->bio_irp_pending=_TRUE;	
	// Build our URB for USBD
	UsbBuildInterruptOrBulkTransferRequest(
				piorw_urb,
				sizeof(struct _URB_BULK_OR_INTERRUPT_TRANSFER),
				PipeHandle,
				(PVOID)wmem,
				NULL, 
				cnt, 
				0, 
				NULL);  

	//
	// call the calss driver to perform the operation
	// pass the URB to the USB driver stack
	//
	nextStack = IoGetNextIrpStackLocation(piorw_irp);
	nextStack->MajorFunction = IRP_MJ_INTERNAL_DEVICE_CONTROL;
	nextStack->Parameters.Others.Argument1 = (PURB)piorw_urb;
	nextStack->Parameters.DeviceIoControl.IoControlCode = IOCTL_INTERNAL_USB_SUBMIT_URB;

	IoSetCompletionRoutine(
				piorw_irp,				// irp to use				
				usb_write_mem_complete,		// routine to call when irp is done
				pio_queue,				// context to pass routine
				TRUE,					// call on success
				TRUE,					// call on error
				TRUE);					// call on cancel
	
	// 
	// Call IoCallDriver to send the irp to the usb port
	//
	NtStatus	= IoCallDriver(pdev->pnextdevobj, piorw_irp);
	usbdstatus = URB_STATUS(piorw_urb);

	//
	// The USB driver should always return STATUS_PENDING when
	// it receives a write irp
	//
	if ((NtStatus != STATUS_PENDING) || USBD_HALTED(usbdstatus) ) {

		if( USBD_HALTED(usbdstatus) ) {

			RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_write_mem():USBD_HALTED(usbdstatus)=%X!\n",USBD_HALTED(usbdstatus)) );
		}
		_func_exit_;
		return;//STATUS_UNSUCCESSFUL;
	}

	_exit_critical_bh(&(pio_queue->lock), &irqL);
	
	_rtw_down_sema(&pio_req->sema);	
	free_ioreq(pio_req, pio_queue);
	

	bwritezero = _FALSE;
       if (pdev->ishighspeed)
	{
		if(cnt> 0 && cnt%512 == 0)
			bwritezero = _TRUE;
			
	}
	else
	{
		if(cnt > 0 && cnt%64 == 0)
			bwritezero = _TRUE;		
	}

	
	if(bwritezero == _TRUE)
	{
		usb_bulkout_zero(pintfhdl, addr);
	}
	
exit:
	
	_func_exit_;
	
}