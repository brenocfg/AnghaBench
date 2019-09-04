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
struct TYPE_3__ {scalar_t__ (* lpGetTransferStatus ) (int /*<<< orphan*/ ,int*,scalar_t__*) ;} ;
typedef  scalar_t__* PUSB_ERROR ;
typedef  int* LPDWORD ;
typedef  TYPE_1__* LPCUSB_FUNCS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ USB_CANCELED_ERROR ; 
 scalar_t__ USB_NO_ERROR ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_hci_ops_os_c_ ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int*,scalar_t__*) ; 

BOOL
GetTransferStatus(
    LPCUSB_FUNCS   pUsbFuncs,
    USB_TRANSFER   hTransfer,
    LPDWORD        pBytesTransferred , // OPTIONAL returns number of bytes transferred
    PUSB_ERROR     pUsbError  	 // returns USB error code
    )
{

    BOOL bRc = TRUE;

    if ( pUsbFuncs->lpGetTransferStatus(hTransfer, pBytesTransferred, pUsbError) ) {
        if ( USB_NO_ERROR != *pUsbError ) {
		RT_TRACE( _module_hci_ops_os_c_, _drv_err_, ("*** CloseTransfer ERROR:%d ***\n", GetLastError()));		
            RT_TRACE( _module_hci_ops_os_c_, _drv_err_, ("GetTransferStatus (BytesTransferred:%d, UsbError:0x%x)\n", pBytesTransferred?*pBytesTransferred:-1, pUsbError?*pUsbError:-1 )); 
        }
    } else {
        RT_TRACE( _module_hci_ops_os_c_, _drv_err_,("*** GetTransferStatus ERROR:%d ***\n", GetLastError())); 
        *pUsbError = USB_CANCELED_ERROR;
        bRc = FALSE;
    }

    return bRc;
}