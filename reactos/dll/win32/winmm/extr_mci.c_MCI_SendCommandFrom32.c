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
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int /*<<< orphan*/  hDriver; } ;
typedef  int /*<<< orphan*/  MCIDEVICEID ;
typedef  TYPE_1__* LPWINE_MCIDRIVER ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  MCIERR_INVALID_DEVICE_ID ; 
 TYPE_1__* MCI_GetDriver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendDriverMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD MCI_SendCommandFrom32(MCIDEVICEID wDevID, UINT16 wMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    DWORD		dwRet = MCIERR_INVALID_DEVICE_ID;
    LPWINE_MCIDRIVER	wmd = MCI_GetDriver(wDevID);

    if (wmd) {
        dwRet = SendDriverMessage(wmd->hDriver, wMsg, dwParam1, dwParam2);
    }
    return dwRet;
}