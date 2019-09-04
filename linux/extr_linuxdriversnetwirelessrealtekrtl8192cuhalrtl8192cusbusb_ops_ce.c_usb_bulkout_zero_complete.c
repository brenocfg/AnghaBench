#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct zero_bulkout_context {int /*<<< orphan*/ * pbuf; TYPE_2__* padapter; } ;
struct xmit_priv {int /*<<< orphan*/  usb_transfer_write_port; } ;
struct TYPE_4__ {TYPE_3__* _lpUsbFuncs; } ;
struct dvobj_priv {TYPE_1__ usb_extension; } ;
struct TYPE_5__ {struct xmit_priv xmitpriv; int /*<<< orphan*/  dvobjpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_6__ {int (* lpIsTransferComplete ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lpCloseTransfer ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lpGetTransferStatus ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ LPVOID ;
typedef  TYPE_3__* LPCUSB_FUNCS ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  USB_CANCELED_ERROR ; 
 int _FALSE ; 
 int _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

DWORD usb_bulkout_zero_complete( LPVOID pZeroContext )
{
	struct zero_bulkout_context *pcontext = (struct zero_bulkout_context *)pZeroContext;
	_adapter * padapter = pcontext->padapter;
    struct dvobj_priv *	pdvobj_priv = (struct dvobj_priv *)&padapter->dvobjpriv;
	LPCUSB_FUNCS usb_funcs_vp = pdvobj_priv->usb_extension._lpUsbFuncs;
	struct xmit_priv  * pxmitpriv	= &padapter->xmitpriv;

	int 	fComplete			=_FALSE;
	DWORD	dwBytesTransferred	= 0;
	DWORD	dwErr				= USB_CANCELED_ERROR;

_func_enter_;

#if 1
				
	(*usb_funcs_vp->lpGetTransferStatus)(pxmitpriv->usb_transfer_write_port, &dwBytesTransferred, &dwErr);
	fComplete = (*usb_funcs_vp->lpIsTransferComplete)(pxmitpriv->usb_transfer_write_port);
	if(fComplete!=_TRUE)
	{
		RT_TRACE( _module_hci_ops_os_c_, _drv_err_, ("usb_bulkout_zero_complete CloseTransfer before complete\n"));
	}
	(*usb_funcs_vp->lpCloseTransfer)(pxmitpriv->usb_transfer_write_port);
	
#endif

	if(pcontext)
	{
		if(pcontext->pbuf)
		{			
			rtw_mfree(pcontext->pbuf, sizeof(int));	
		}	

		rtw_mfree((u8*)pcontext, sizeof(struct zero_bulkout_context));	
	}	

_func_exit_;

	return ERROR_SUCCESS;
	

}