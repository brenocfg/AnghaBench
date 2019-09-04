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
struct recv_priv {int /*<<< orphan*/  allrxreturnevt; scalar_t__ precv_buf; scalar_t__ rx_pending_cnt; int /*<<< orphan*/  lock; } ;
struct recv_buf {scalar_t__ irp_pending; int /*<<< orphan*/  pirp; } ;
struct dvobj_priv {int dummy; } ;
typedef  scalar_t__ sint ;
struct TYPE_3__ {struct recv_priv recvpriv; struct dvobj_priv dvobjpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  IoCancelIrp (int /*<<< orphan*/ ) ; 
 scalar_t__ NR_RECVBUFF ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  _rtw_down_sema (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinunlock (int /*<<< orphan*/ *) ; 

void usb_read_port_cancel(_adapter *padapter)
{	
	struct recv_buf  *precvbuf;
	sint i;
	struct dvobj_priv   *pdev = &padapter->dvobjpriv;
	struct recv_priv *precvpriv=&padapter->recvpriv;	
		
	RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("\n ==>usb_read_port_cancel\n"));

	_rtw_spinlock(&precvpriv->lock);
	precvpriv->rx_pending_cnt--; //decrease 1 for Initialize ++ 
	_rtw_spinunlock(&precvpriv->lock);

	if (precvpriv->rx_pending_cnt)
	{
		// Canceling Pending Recv Irp
		precvbuf = (struct recv_buf  *)precvpriv->precv_buf;
		
		for( i = 0; i < NR_RECVBUFF; i++ )
		{
			if (precvbuf->irp_pending == _TRUE)
			{	
				IoCancelIrp(precvbuf->pirp);
				RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port_cancel() :IoCancelIrp\n"));
			}
			
			precvbuf++;
		}
		
		_rtw_down_sema(&precvpriv->allrxreturnevt);
		
		RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("usb_read_port_cancel:down sema\n"));

	}
	
	RT_TRACE(_module_hci_ops_os_c_,_drv_err_,("<==usb_read_port_cancel\n"));
	
}