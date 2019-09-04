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
struct dvobj_priv {int dummy; } ;
typedef  scalar_t__ LPVOID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  _drv_debug_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 

DWORD usbctrl_vendorreq_complete(LPVOID lpvNotifyParameter)
{
	struct dvobj_priv  *pdvobjpriv = (struct dvobj_priv*)lpvNotifyParameter;

	RT_TRACE(_module_hci_ops_os_c_,_drv_debug_,("+usbctrl_vendorreq_complete\n"));
	
    return STATUS_SUCCESS;
}