#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xmit_priv {int /*<<< orphan*/  tx_retevt; scalar_t__ pxmit_frame_buf; scalar_t__ txirp_cnt; int /*<<< orphan*/  lock; } ;
struct xmit_frame {scalar_t__* bpending; int /*<<< orphan*/ * pxmit_irp; } ;
struct dvobj_priv {int dummy; } ;
typedef  scalar_t__ sint ;
struct TYPE_3__ {struct xmit_priv xmitpriv; struct dvobj_priv dvobjpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  IoCancelIrp (int /*<<< orphan*/ ) ; 
 scalar_t__ NR_XMITFRAME ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_down_sema (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinunlock (int /*<<< orphan*/ *) ; 

void usb_write_port_cancel(_adapter *padapter)
{

	sint i,j;
	struct dvobj_priv   *pdev = &padapter->dvobjpriv;
	struct xmit_priv *pxmitpriv=&padapter->xmitpriv;
	struct xmit_frame *pxmitframe;

	_rtw_spinlock(&pxmitpriv->lock);
	pxmitpriv->txirp_cnt--; //decrease 1 for Initialize ++
	_rtw_spinunlock(&pxmitpriv->lock);
	
	if (pxmitpriv->txirp_cnt) 
	{
		// Canceling Pending Recv Irp
		pxmitframe= (struct xmit_frame *)pxmitpriv->pxmit_frame_buf;
		
		for( i = 0; i < NR_XMITFRAME; i++ )
		{
			for(j=0;j<8;j++)
			{
				if (pxmitframe->bpending[j]==_TRUE)
				{			
					IoCancelIrp(pxmitframe->pxmit_irp[j]);		
					RT_TRACE(_module_hci_ops_os_c_,_drv_err_,(" usb_write_port_cancel() :IoCancelIrp\n"));

				}
			}
			
			pxmitframe++;
		}

		_rtw_down_sema(&(pxmitpriv->tx_retevt));
		
	}

}