#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct zero_bulkout_context {unsigned char* pbuf; TYPE_2__* padapter; int /*<<< orphan*/ * pirp; int /*<<< orphan*/ * purb; } ;
struct usb_device {int dummy; } ;
struct intf_hdl {scalar_t__ padapter; } ;
struct dvobj_priv {struct usb_device* pusbdev; } ;
struct TYPE_4__ {scalar_t__ pnp_bstop_trx; } ;
struct TYPE_5__ {TYPE_1__ pwrctrlpriv; scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; } ;
typedef  TYPE_2__ _adapter ;
typedef  int /*<<< orphan*/ * PURB ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 struct dvobj_priv* adapter_to_dvobj (TYPE_2__*) ; 
 scalar_t__ rtw_zmalloc (int) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_bulkout_zero_complete ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ *,struct usb_device*,int,unsigned char*,int,int /*<<< orphan*/ ,struct zero_bulkout_context*) ; 
 int usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 usb_bulkout_zero(struct intf_hdl *pintfhdl, u32 addr)
{	
	int pipe, status, len;
	u32 ret;
	unsigned char *pbuf;
	struct zero_bulkout_context *pcontext;
	PURB	purb = NULL;	
	_adapter *padapter = (_adapter *)pintfhdl->padapter;
	struct dvobj_priv *pdvobj = adapter_to_dvobj(padapter);	
	struct usb_device *pusbd = pdvobj->pusbdev;

	//DBG_871X("%s\n", __func__);
	
		
	if((padapter->bDriverStopped) || (padapter->bSurpriseRemoved) ||(padapter->pwrctrlpriv.pnp_bstop_trx))
	{		
		return _FAIL;
	}
	

	pcontext = (struct zero_bulkout_context *)rtw_zmalloc(sizeof(struct zero_bulkout_context));

	pbuf = (unsigned char *)rtw_zmalloc(sizeof(int));	
    	purb = usb_alloc_urb(0, GFP_ATOMIC);
      	
	len = 0;
	pcontext->pbuf = pbuf;
	pcontext->purb = purb;
	pcontext->pirp = NULL;
	pcontext->padapter = padapter;

	
	//translate DMA FIFO addr to pipehandle
	//pipe = ffaddr2pipehdl(pdvobj, addr);	

	usb_fill_bulk_urb(purb, pusbd, pipe, 
       				pbuf,
              			len,
              			usb_bulkout_zero_complete,
              			pcontext);//context is pcontext

	status = usb_submit_urb(purb, GFP_ATOMIC);

	if (!status)
	{		
		ret= _SUCCESS;
	}
	else
	{
		ret= _FAIL;
	}
	
	
	return _SUCCESS;

}