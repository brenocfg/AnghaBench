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
typedef  int /*<<< orphan*/  USB_TRANSFER ;
struct TYPE_3__ {int /*<<< orphan*/  (* lpCloseTransfer ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* LPCUSB_FUNCS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

BOOL
CloseTransferHandle(
    LPCUSB_FUNCS   pUsbFuncs,
    USB_TRANSFER   hTransfer
    )
{
    BOOL bRc = TRUE;

    // This assert may fail on suprise remove,
    // but should pass during normal I/O.
    // ASSERT( pUsbFuncs->lpIsTransferComplete(hTransfer) ); 

    // CloseTransfer aborts any pending transfers
    if ( !pUsbFuncs->lpCloseTransfer(hTransfer) ) {
     
	RT_TRACE( _module_hci_ops_os_c_, _drv_err_, ("*** CloseTransfer ERROR:%d ***\n", GetLastError()));	
        bRc = FALSE;
    }

    return bRc;
}