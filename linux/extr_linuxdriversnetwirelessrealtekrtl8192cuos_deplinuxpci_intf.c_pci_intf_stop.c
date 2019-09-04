#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  xmit_tasklet; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq_prepare_beacon_tasklet; int /*<<< orphan*/  recv_tasklet; } ;
struct TYPE_10__ {scalar_t__ bSurpriseRemoved; TYPE_2__ xmitpriv; TYPE_1__ recvpriv; } ;
typedef  TYPE_3__ _adapter ;
struct TYPE_11__ {scalar_t__ irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_intfs_c_ ; 
 TYPE_6__* adapter_to_dvobj (TYPE_3__*) ; 
 int /*<<< orphan*/  rtw_hal_disable_interrupt (TYPE_3__*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_intf_stop(_adapter *padapter)
{

	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("+pci_intf_stop\n"));

	//Disable hw interrupt
	if(padapter->bSurpriseRemoved == _FALSE)
	{
		//device still exists, so driver can do i/o operation
		rtw_hal_disable_interrupt(padapter);
		tasklet_disable(&(padapter->recvpriv.recv_tasklet));
		tasklet_disable(&(padapter->recvpriv.irq_prepare_beacon_tasklet));
		tasklet_disable(&(padapter->xmitpriv.xmit_tasklet));

#ifdef CONFIG_CONCURRENT_MODE
		/*	This function only be called at driver removing. disable buddy_adapter too
			don't disable interrupt of buddy_adapter because it is same as primary.
		*/
		if (padapter->pbuddy_adapter){
			tasklet_disable(&(padapter->pbuddy_adapter->recvpriv.recv_tasklet));
			tasklet_disable(&(padapter->pbuddy_adapter->recvpriv.irq_prepare_beacon_tasklet));
			tasklet_disable(&(padapter->pbuddy_adapter->xmitpriv.xmit_tasklet));
		}
#endif
		RT_TRACE(_module_hci_intfs_c_,_drv_err_,("pci_intf_stop: SurpriseRemoved==_FALSE\n"));
	}
	else
	{
		// Clear irq_enabled to prevent handle interrupt function.
		adapter_to_dvobj(padapter)->irq_enabled = 0;
	}

	RT_TRACE(_module_hci_intfs_c_,_drv_err_,("-pci_intf_stop\n"));

}