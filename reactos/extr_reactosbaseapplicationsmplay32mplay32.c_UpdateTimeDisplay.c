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
typedef  int /*<<< orphan*/  szTime ;
struct TYPE_2__ {int dwReturn; int /*<<< orphan*/  dwItem; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ MCI_STATUS_PARMS ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int MAX_MCISTR ; 
#define  MCI_FORMAT_MILLISECONDS 128 
 int /*<<< orphan*/  MCI_STATUS ; 
 int /*<<< orphan*/  MCI_STATUS_ITEM ; 
 int /*<<< orphan*/  MCI_STATUS_POSITION ; 
 int /*<<< orphan*/  MCI_STATUS_TIME_FORMAT ; 
 int /*<<< orphan*/  SetWindowText (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringCbPrintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,...) ; 
 int /*<<< orphan*/ * _T (char*) ; 
 int /*<<< orphan*/  mciSendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wDeviceId ; 

void UpdateTimeDisplay(HWND hwnd)
{
    MCI_STATUS_PARMS mciStatus;
    TCHAR szTime[MAX_MCISTR];
    DWORD dwTimeFormat;

    if (!wDeviceId)
    {
        SetWindowText(hwnd, _T(""));
        return;
    }

    mciStatus.dwItem = MCI_STATUS_TIME_FORMAT;
    mciStatus.dwReturn = 0;
    mciSendCommand(wDeviceId, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&mciStatus);
    dwTimeFormat = mciStatus.dwReturn;

    mciStatus.dwItem = MCI_STATUS_POSITION;
    mciStatus.dwReturn = 0;
    mciSendCommand(wDeviceId, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&mciStatus);

    switch(dwTimeFormat)
    {
        case MCI_FORMAT_MILLISECONDS:
        {
            int s, m, h;

            s = (mciStatus.dwReturn / 1000) % 60;
            m = ((mciStatus.dwReturn / (1000*60)) % 60);
            h = ((mciStatus.dwReturn / (1000*60*60)) % 24);
            StringCbPrintf(szTime, sizeof(szTime), _T("%02lu:%02lu:%02lu"), h, m, s);
            break;
        }

        /* The time format is unknown, so use the returned position as is */
        default:
        {
            StringCbPrintf(szTime, sizeof(szTime), _T("%lu"), mciStatus.dwReturn);
            break;
        }
    }

    SetWindowText(hwnd, szTime);
}