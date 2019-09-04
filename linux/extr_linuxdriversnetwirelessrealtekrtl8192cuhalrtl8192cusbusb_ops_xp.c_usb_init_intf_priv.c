#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct intf_priv {int max_iosz; int io_irp_cnt; int /*<<< orphan*/ * allocated_io_rwmem; int /*<<< orphan*/  io_retevt; int /*<<< orphan*/  bio_irp_pending; int /*<<< orphan*/  piorw_irp; int /*<<< orphan*/ * piorw_urb; int /*<<< orphan*/ * io_rwmem; scalar_t__ io_rsz; scalar_t__ io_wsz; int /*<<< orphan*/  io_timer; int /*<<< orphan*/  intf_status; scalar_t__ intf_dev; } ;
struct dvobj_priv {scalar_t__ nextdevstacksz; scalar_t__ ishighspeed; TYPE_1__* padapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  hndis_adapter; } ;
typedef  TYPE_1__ _adapter ;
typedef  int /*<<< orphan*/  URB ;
typedef  int /*<<< orphan*/ * PURB ;

/* Variables and functions */
 scalar_t__ ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IoAllocateIrp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _IOREADY ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _init_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct intf_priv*) ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_init_sema (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_irp_timeout_handler ; 
 int /*<<< orphan*/  rtw_mfree (scalar_t__*,int) ; 
 int /*<<< orphan*/ * rtw_zmalloc (int) ; 

uint usb_init_intf_priv(struct intf_priv *pintfpriv)
{
	        
	PURB	piorw_urb;
	u8		NextDeviceStackSize;
	struct dvobj_priv   *pdev = (struct dvobj_priv   *)pintfpriv->intf_dev;
	_adapter * padapter=pdev->padapter;

_func_enter_;
	
	RT_TRACE(_module_hci_ops_os_c_,_drv_info_,("\n +usb_init_intf_priv\n"));

	pintfpriv->intf_status = _IOREADY;

       if(pdev->ishighspeed) pintfpriv->max_iosz =  128;
	else pintfpriv->max_iosz =  64;	


	_init_timer(&pintfpriv->io_timer, padapter->hndis_adapter, io_irp_timeout_handler, pintfpriv);

	
	RT_TRACE(_module_hci_ops_os_c_,_drv_info_,("usb_init_intf_priv:pintfpriv->max_iosz:%d\n",pintfpriv->max_iosz));

	pintfpriv->io_wsz = 0;
	pintfpriv->io_rsz = 0;	
	
 	pintfpriv->allocated_io_rwmem = rtw_zmalloc(pintfpriv->max_iosz +4); 
	
   	if (pintfpriv->allocated_io_rwmem == NULL){
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n usb_init_intf_priv:pintfpriv->allocated_io_rwmem == NULL\n"));
    		goto usb_init_intf_priv_fail;
   	}

	pintfpriv->io_rwmem = pintfpriv->allocated_io_rwmem +  4 \
					-( (u32)(pintfpriv->allocated_io_rwmem) & 3);
	

     
     NextDeviceStackSize = (u8)pdev->nextdevstacksz;//pintfpriv->pUsbDevObj->StackSize + 1; 

      piorw_urb = (PURB)ExAllocatePool(NonPagedPool, sizeof(URB) ); 
      if(piorw_urb == NULL) 
	  goto usb_init_intf_priv_fail;
	  
      pintfpriv->piorw_urb = piorw_urb;

      pintfpriv->piorw_irp = IoAllocateIrp(NextDeviceStackSize , FALSE);	 
    

      pintfpriv->io_irp_cnt=1;
      pintfpriv->bio_irp_pending=_FALSE;
	 
     _rtw_init_sema(&(pintfpriv->io_retevt), 0);//NdisInitializeEvent(&pintfpriv->io_irp_return_evt);

_func_exit_;
	return _SUCCESS;

usb_init_intf_priv_fail:

	if (pintfpriv->allocated_io_rwmem)
		rtw_mfree((u8 *)(pintfpriv->allocated_io_rwmem), pintfpriv->max_iosz +4);
	
	if(piorw_urb)
		ExFreePool(piorw_urb);	

	RT_TRACE(_module_hci_ops_os_c_,_drv_info_,("\n -usb_init_intf_priv(usb_init_intf_priv_fail)\n"));

_func_exit_;	
	return _FAIL;
		
}