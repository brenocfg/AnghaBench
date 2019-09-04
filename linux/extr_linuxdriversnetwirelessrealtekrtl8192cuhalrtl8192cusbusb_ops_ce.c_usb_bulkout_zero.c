#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct zero_bulkout_context {unsigned char* pbuf; TYPE_3__* padapter; int /*<<< orphan*/ * pirp; int /*<<< orphan*/ * purb; } ;
struct xmit_priv {int /*<<< orphan*/  usb_transfer_write_port; } ;
struct intf_hdl {scalar_t__ adapter; } ;
struct TYPE_5__ {TYPE_4__* _lpUsbFuncs; } ;
struct dvobj_priv {TYPE_1__ usb_extension; } ;
struct TYPE_6__ {scalar_t__ pnp_bstop_trx; } ;
struct TYPE_7__ {TYPE_2__ pwrctrlpriv; scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; struct xmit_priv xmitpriv; int /*<<< orphan*/  dvobjpriv; } ;
typedef  TYPE_3__ _adapter ;
typedef  int /*<<< orphan*/  USB_PIPE ;
struct TYPE_8__ {int /*<<< orphan*/  (* lpIssueBulkTransfer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zero_bulkout_context*,int /*<<< orphan*/ ,scalar_t__,unsigned char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__* LPCUSB_FUNCS ;

/* Variables and functions */
 int /*<<< orphan*/  USB_OUT_TRANSFER ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  ffaddr2pipehdl (struct dvobj_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_zmalloc (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zero_bulkout_context*,int /*<<< orphan*/ ,scalar_t__,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_bulkout_zero_complete ; 

u32 usb_bulkout_zero(struct intf_hdl *pintfhdl, u32 addr)
{	
	struct zero_bulkout_context *pcontext;
	unsigned char *pbuf;
	u8 len = 0 ;
	_adapter *padapter = (_adapter *)pintfhdl->adapter;
	struct dvobj_priv	*pdvobj = (struct dvobj_priv *)&padapter->dvobjpriv;	
	struct xmit_priv	* pxmitpriv     = &padapter->xmitpriv;
     

	LPCUSB_FUNCS usb_funcs_vp = pdvobj->usb_extension._lpUsbFuncs;

	USB_PIPE	hPipe;

_func_enter_;

	if((padapter->bDriverStopped) || (padapter->bSurpriseRemoved) ||(padapter->pwrctrlpriv.pnp_bstop_trx))
	{		
		return _FAIL;
	}


	pcontext = (struct zero_bulkout_context *)rtw_zmalloc(sizeof(struct zero_bulkout_context));

	pbuf = (unsigned char *)rtw_zmalloc(sizeof(int));	

	len = 0;
	
	pcontext->pbuf = pbuf;
	pcontext->purb = NULL;
	pcontext->pirp = NULL;
	pcontext->padapter = padapter;
                    

//translate DMA FIFO addr to pipehandle
	hPipe = ffaddr2pipehdl(pdvobj, addr);




	pxmitpriv->usb_transfer_write_port = (*usb_funcs_vp->lpIssueBulkTransfer)(
						        hPipe, usb_bulkout_zero_complete, 
						        pcontext, USB_OUT_TRANSFER,
					    	    len, pbuf, 0);

	
_func_exit_;
	
	return _SUCCESS;

}