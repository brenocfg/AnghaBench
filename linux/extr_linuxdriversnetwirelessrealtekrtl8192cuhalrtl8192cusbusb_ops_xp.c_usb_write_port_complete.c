#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct xmit_priv {scalar_t__ txirp_cnt; int /*<<< orphan*/  tx_retevt; int /*<<< orphan*/  lock; } ;
struct xmit_frame {int* sz; void** bpending; TYPE_3__** pxmit_irp; TYPE_2__* padapter; struct xmit_buf* pxmitbuf; } ;
struct xmit_buf {int dummy; } ;
struct intf_hdl {int dummy; } ;
struct io_queue {struct intf_hdl intf; } ;
struct dvobj_priv {int dummy; } ;
struct TYPE_7__ {scalar_t__ bSurpriseRemoved; int /*<<< orphan*/  bDriverStopped; struct xmit_priv xmitpriv; scalar_t__ pio_queue; int /*<<< orphan*/  dvobjpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_6__ {scalar_t__ Status; } ;
struct TYPE_8__ {scalar_t__ Cancel; TYPE_1__ IoStatus; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_3__* PIRP ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ STATUS_MORE_PROCESSING_REQUIRED ; 
 scalar_t__ STATUS_SUCCESS ; 
 void* _FALSE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_spinlock_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinunlock_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_up_sema (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl8192cu_xmitframe_complete (TYPE_2__*,struct xmit_priv*,struct xmit_buf*) ; 
 int /*<<< orphan*/  rtw_free_xmitframe (struct xmit_priv*,struct xmit_frame*) ; 

NTSTATUS usb_write_port_complete(
	PDEVICE_OBJECT	pUsbDevObj,
	PIRP				pIrp,
	PVOID			pTxContext
) 
{	
	u32	i, bIrpSuccess, sz;
	NTSTATUS	status = STATUS_SUCCESS;
	u8 *ptr;
	struct xmit_frame	*pxmitframe = (struct xmit_frame *) pTxContext;
        struct xmit_buf *pxmitbuf = pxmitframe->pxmitbuf;
	_adapter			*padapter = pxmitframe->padapter;
	struct dvobj_priv	*pdev =	(struct dvobj_priv *)&padapter->dvobjpriv;	
	struct io_queue	*pio_queue = (struct io_queue *)padapter->pio_queue;
	struct intf_hdl	*pintfhdl = &(pio_queue->intf);
       struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;		
	   
_func_enter_;

	RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("+usb_write_port_complete\n"));

	_rtw_spinlock_ex(&pxmitpriv->lock);	
	pxmitpriv->txirp_cnt--;
	_rtw_spinunlock_ex(&pxmitpriv->lock);
	
	if(pxmitpriv->txirp_cnt==0){
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_write_port_complete: txirp_cnt== 0, set allrxreturnevt!\n"));		
		_rtw_up_sema(&(pxmitpriv->tx_retevt));
	}
	
	status = pIrp->IoStatus.Status;

	if( status == STATUS_SUCCESS ) 
		bIrpSuccess = _TRUE;	
	else	
		bIrpSuccess = _FALSE;
	
	if( pIrp->Cancel == _TRUE )
	{		
	    if(pxmitframe !=NULL)
	    {	       
	    		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n usb_write_port_complete:pIrp->Cancel == _TRUE,(pxmitframe !=NULL\n"));
			rtw_free_xmitframe(pxmitpriv, pxmitframe);			
	    }
		  	 
	     return STATUS_MORE_PROCESSING_REQUIRED;
	}

	if(padapter->bSurpriseRemoved)
	{
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_write_port_complete:bDriverStopped(%d) OR bSurpriseRemoved(%d)", padapter->bDriverStopped, padapter->bSurpriseRemoved));
		return STATUS_MORE_PROCESSING_REQUIRED;
	}


	//
	// Send 0-byte here if necessary.
	//
	// <Note> 
	// 1. We MUST keep at most one IRP pending in each endpoint, otherwise USB host controler driver will hang.
	// Besides, even 0-byte IRP shall be count into #IRP sent down, so, we send 0-byte here instead of TxFillDescriptor8187().
	// 2. If we don't count 0-byte IRP into an #IRP sent down, Tx will stuck when we download files via BT and 
	// play online video on XP SP1 EHCU.
	// 2005.12.26, by rcnjko.
	//

	
	for(i=0; i< 8; i++)
	{
            if(pIrp == pxmitframe->pxmit_irp[i])
            {
		    pxmitframe->bpending[i] = _FALSE;//
		    //ac_tag = pxmitframe->ac_tag[i];
                  sz = pxmitframe->sz[i];
		    break;		  
            }
	}

#if 0	
	pxmitframe->fragcnt--;
	if(pxmitframe->fragcnt == 0)// if((pxmitframe->fragcnt == 0) && (pxmitframe->irpcnt == 8)){
	{
		//RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n usb_write_port_complete:pxmitframe->fragcnt == 0\n"));
		rtw_free_xmitframe(pxmitpriv,pxmitframe);	          
      	}
#else	

	//not to consider tx fragment
	rtw_free_xmitframe(pxmitpriv, pxmitframe);		

#endif	

	rtl8192cu_xmitframe_complete(padapter, pxmitpriv, pxmitbuf);

_func_exit_;

	return STATUS_MORE_PROCESSING_REQUIRED;

}