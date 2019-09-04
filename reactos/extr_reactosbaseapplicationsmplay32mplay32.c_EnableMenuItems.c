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
struct TYPE_2__ {int /*<<< orphan*/  hWnd; } ;
typedef  int /*<<< orphan*/  MCI_GENERIC_PARMS ;
typedef  TYPE_1__ MCI_DGV_WINDOW_PARMSW ;
typedef  int /*<<< orphan*/  MCI_DGV_RECT_PARMS ;
typedef  scalar_t__ MCIERROR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  EnableMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDM_CLOSE_FILE ; 
 int /*<<< orphan*/  IDM_DEVPROPS ; 
 int /*<<< orphan*/  IDM_SWITCHVIEW ; 
 int /*<<< orphan*/  MCI_CONFIGURE ; 
 int MCI_DGV_WHERE_SOURCE ; 
 int MCI_DGV_WINDOW_HWND ; 
 int MCI_TEST ; 
 int /*<<< orphan*/  MCI_WHERE ; 
 int /*<<< orphan*/  MCI_WINDOW ; 
 int MF_BYCOMMAND ; 
 int MF_ENABLED ; 
 int /*<<< orphan*/  hMainMenu ; 
 scalar_t__ mciSendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wDeviceId ; 

void EnableMenuItems(HWND hwnd)
{
    MCIERROR mciError;
    MCI_GENERIC_PARMS mciGeneric;
    MCI_DGV_RECT_PARMS mciVideoRect;
    MCI_DGV_WINDOW_PARMSW mciVideoWindow;

    EnableMenuItem(hMainMenu, IDM_CLOSE_FILE, MF_BYCOMMAND | MF_ENABLED);

    mciError = mciSendCommand(wDeviceId, MCI_CONFIGURE, MCI_TEST, (DWORD_PTR)&mciGeneric);
    if (mciError == 0)
    {
        EnableMenuItem(hMainMenu, IDM_DEVPROPS, MF_BYCOMMAND | MF_ENABLED);
    }

    mciVideoWindow.hWnd = hwnd;

    mciError = mciSendCommand(wDeviceId, MCI_WINDOW, MCI_DGV_WINDOW_HWND | MCI_TEST, (DWORD_PTR)&mciVideoWindow);
    if (!mciError)
    {
        mciError = mciSendCommand(wDeviceId, MCI_WHERE, MCI_DGV_WHERE_SOURCE | MCI_TEST, (DWORD_PTR)&mciVideoRect);
        if (!mciError)
        {
            EnableMenuItem(hMainMenu, IDM_SWITCHVIEW, MF_BYCOMMAND | MF_ENABLED);
        }
    }
}