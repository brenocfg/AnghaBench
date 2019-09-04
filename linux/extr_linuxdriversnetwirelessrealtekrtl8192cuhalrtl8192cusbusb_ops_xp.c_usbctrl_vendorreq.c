#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct intf_priv {scalar_t__ intf_dev; } ;
struct dvobj_priv {int dummy; } ;
struct _URB_CONTROL_VENDOR_OR_CLASS_REQUEST {int dummy; } ;
typedef  int /*<<< orphan*/ * PURB ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  URB_FUNCTION_VENDOR_DEVICE ; 
 unsigned long USBD_TRANSFER_DIRECTION_IN ; 
 int /*<<< orphan*/  UsbBuildVendorRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _FALSE ; 
 int _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  sync_callusbd (struct dvobj_priv*,int /*<<< orphan*/ *) ; 

int usbctrl_vendorreq(struct intf_priv *pintfpriv, u8 request, u16 value, u16 index, void *pdata, u16 len, u8 requesttype)
{
	PURB			purb;
	u8				ret;
	unsigned long		transferflags;
	NTSTATUS		ntstatus;

	struct dvobj_priv  *pdvobjpriv = (struct dvobj_priv  *)pintfpriv->intf_dev;   
	
	_func_enter_;

	ret=_TRUE;
	purb = (PURB)ExAllocatePool(NonPagedPool, sizeof(struct _URB_CONTROL_VENDOR_OR_CLASS_REQUEST) );
	if(purb == NULL) {
		
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usbctrl_vendorreq(): Failed to allocate urb !!!\n"));
		ret =_FALSE;
		goto exit;
	}

	if (requesttype == 0x01) {
		transferflags = USBD_TRANSFER_DIRECTION_IN;//read_in
	} else {
		transferflags= 0;//write_out
	}

	UsbBuildVendorRequest(
			purb, 		//Pointer to an URB that is to be formatted as a vendor or class request. 
			URB_FUNCTION_VENDOR_DEVICE,	//Indicates the URB is a vendor-defined request for a USB device. 
			sizeof(struct _URB_CONTROL_VENDOR_OR_CLASS_REQUEST),  //Specifies the length, in bytes, of the URB. 
			transferflags, 	//TransferFlags 
			0,			//ReservedBits 
			request, 	//Request 
			value, 		//Value 
			index,		//Index
			pdata,		//TransferBuffer 
			NULL,		//TransferBufferMDL 
			len,			//TransferBufferLength 
			NULL		//Link 
	);

	ntstatus = sync_callusbd(pdvobjpriv, purb);
	if(!NT_SUCCESS(ntstatus))
	{
		ExFreePool(purb);
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,(" usbctrl_vendorreq() : SOMETHING WRONG\n") );
		ret = _FALSE;
		goto exit;
	}

	ExFreePool(purb);

exit:	
	_func_exit_;
	
	return ret;	

}