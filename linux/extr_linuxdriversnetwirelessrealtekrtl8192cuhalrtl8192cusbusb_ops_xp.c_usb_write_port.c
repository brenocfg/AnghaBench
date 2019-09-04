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
struct xmit_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  txirp_cnt; } ;
struct xmit_frame {scalar_t__* bpending; int* sz; int /*<<< orphan*/  mem_addr; TYPE_6__** pxmit_irp; int /*<<< orphan*/ ** pxmit_urb; } ;
struct intf_hdl {scalar_t__ adapter; } ;
struct dvobj_priv {int /*<<< orphan*/  pnextdevobj; scalar_t__ ishighspeed; } ;
struct _URB_BULK_OR_INTERRUPT_TRANSFER {int dummy; } ;
struct TYPE_12__ {scalar_t__ pnp_bstop_trx; } ;
struct TYPE_16__ {int bDriverStopped; int bSurpriseRemoved; TYPE_1__ pwrctrlpriv; struct xmit_priv xmitpriv; int /*<<< orphan*/  dvobjpriv; } ;
typedef  TYPE_5__ _adapter ;
typedef  int /*<<< orphan*/  USBD_STATUS ;
struct TYPE_14__ {int /*<<< orphan*/  IoControlCode; } ;
struct TYPE_13__ {int /*<<< orphan*/ * Argument1; } ;
struct TYPE_15__ {TYPE_3__ DeviceIoControl; TYPE_2__ Others; } ;
struct TYPE_18__ {TYPE_4__ Parameters; int /*<<< orphan*/  MajorFunction; } ;
struct TYPE_17__ {scalar_t__ Cancel; } ;
typedef  int /*<<< orphan*/ * PURB ;
typedef  TYPE_6__* PIRP ;
typedef  TYPE_7__* PIO_STACK_LOCATION ;
typedef  scalar_t__ NDIS_STATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_INTERNAL_USB_SUBMIT_URB ; 
 int /*<<< orphan*/  IRP_MJ_INTERNAL_DEVICE_CONTROL ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_7__* IoGetNextIrpStackLocation (TYPE_6__*) ; 
 int /*<<< orphan*/  IoSetCompletionRoutine (TYPE_6__*,int /*<<< orphan*/ ,struct xmit_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ STATUS_PENDING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  URB_STATUS (int /*<<< orphan*/ *) ; 
 scalar_t__ USBD_HALTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UsbBuildInterruptOrBulkTransferRequest (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _FAIL ; 
 scalar_t__ _FALSE ; 
 int _SUCCESS ; 
 int _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_spinlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffaddr2pipehdl (struct dvobj_priv*,int) ; 
 int /*<<< orphan*/  usb_bulkout_zero (struct intf_hdl*,int) ; 
 int /*<<< orphan*/  usb_write_port_complete ; 

u32 usb_write_port(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *wmem)
{
       u32 i, bwritezero;      	
	u8 *ptr;
	PIO_STACK_LOCATION	nextStack;
	USBD_STATUS		usbdstatus;
	HANDLE				PipeHandle;	
	PIRP					pirp = NULL;
	PURB				purb = NULL;	
	NDIS_STATUS			ndisStatus = NDIS_STATUS_SUCCESS;
	_adapter *padapter = (_adapter *)pintfhdl->adapter;
	struct dvobj_priv	*pNdisCEDvice = (struct dvobj_priv   *)&padapter->dvobjpriv;	
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct xmit_frame *pxmitframe = (struct xmit_frame *)wmem;

_func_enter_;

	if((padapter->bDriverStopped) || (padapter->bSurpriseRemoved) ||(padapter->pwrctrlpriv.pnp_bstop_trx))
	{
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_write_port:( padapter->bDriverStopped ||padapter->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n"));
		return _FAIL;
	}
	

	for(i=0; i<8; i++)
       {
		if(pxmitframe->bpending[i] == _FALSE)
		{
			_rtw_spinlock(&pxmitpriv->lock);	
			pxmitpriv->txirp_cnt++;
			pxmitframe->bpending[i]  = _TRUE;
			_rtw_spinunlock(&pxmitpriv->lock);
			
			pxmitframe->sz[i] = cnt;
			purb	= pxmitframe->pxmit_urb[i];
			pirp	= pxmitframe->pxmit_irp[i];
			
			//pxmitframe->ac_tag[i] = ac_tag;
			
			break;	 
		}
       }	

	bwritezero = _FALSE;
       if (pNdisCEDvice->ishighspeed)
	{
		if(cnt> 0 && cnt%512 == 0)
		{
			RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("ishighspeed, cnt=%d\n", cnt));
			//cnt=cnt+1;
			bwritezero = _TRUE;
		}	
	}
	else
	{
		if(cnt > 0 && cnt%64 == 0)
		{
			RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("cnt=%d\n", cnt));
			//cnt=cnt+1;
			bwritezero = _TRUE;
		}	
	}
	

#ifdef NDIS51_MINIPORT
	IoReuseIrp(pirp, STATUS_SUCCESS);
#else
	pirp->Cancel = _FALSE;
#endif


	//translate DMA FIFO addr to pipehandle
	PipeHandle = ffaddr2pipehdl(pNdisCEDvice, addr);	


	// Build our URB for USBD
	UsbBuildInterruptOrBulkTransferRequest(
				purb,
				sizeof(struct _URB_BULK_OR_INTERRUPT_TRANSFER),
				PipeHandle,
				pxmitframe->mem_addr, 
				NULL, 
				cnt, 
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
				               usb_write_port_complete,	// callback routine
				               pxmitframe,				// context 
				               TRUE,					// call on success
				               TRUE,					// call on error
				               TRUE);					// call on cancel

	
	// Call IoCallDriver to send the irp to the usb bus driver
	//
	ndisStatus = IoCallDriver(pNdisCEDvice->pnextdevobj, pirp);
	usbdstatus = URB_STATUS(purb);

	if( USBD_HALTED(usbdstatus) )
	{
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n usb_write_port(): USBD_HALTED(usbdstatus)=%x set bDriverStopped TRUE!\n\n",USBD_HALTED(usbdstatus)) );
		padapter->bDriverStopped=_TRUE;
		padapter->bSurpriseRemoved=_TRUE;
	}

	//
	// The usb bus driver should always return STATUS_PENDING when bulk out irp async
	//
	if ( ndisStatus != STATUS_PENDING )
	{
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n usb_write_port(): ndisStatus(%x) != STATUS_PENDING!\n\n", ndisStatus));
		
		_func_exit_;
		
		return _FAIL;
	} 	
	
	if(bwritezero == _TRUE)
	{
		usb_bulkout_zero(pintfhdl, addr);
	}

	
_func_exit_;
	
	return _SUCCESS;

}