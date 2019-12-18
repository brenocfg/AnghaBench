#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dwReturn; int /*<<< orphan*/  dwItem; } ;
typedef  TYPE_1__ MCI_STATUS_PARMS ;
typedef  scalar_t__ MCIERROR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  MCI_MODE_NOT_READY ; 
 int /*<<< orphan*/  MCI_STATUS ; 
 int MCI_STATUS_ITEM ; 
 int /*<<< orphan*/  MCI_STATUS_MODE ; 
 int MCI_WAIT ; 
 int /*<<< orphan*/  ShowMCIError (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mciSendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wDeviceId ; 

__attribute__((used)) static DWORD
GetDeviceMode(HWND hwnd)
{
    MCIERROR mciError;
    MCI_STATUS_PARMS mciStatus;

    mciStatus.dwItem = MCI_STATUS_MODE;
    mciError = mciSendCommand(wDeviceId, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD_PTR)&mciStatus);
    if (mciError != 0)
    {
        ShowMCIError(hwnd, mciError);
        return MCI_MODE_NOT_READY;
    }

    return mciStatus.dwReturn;
}