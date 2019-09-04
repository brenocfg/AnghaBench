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
typedef  int /*<<< orphan*/  szNewTitle ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int GetDeviceMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_MODE_NOT_READY ; 
 int /*<<< orphan*/  IDS_MODE_OPEN ; 
 int /*<<< orphan*/  IDS_MODE_PAUSE ; 
 int /*<<< orphan*/  IDS_MODE_PLAY ; 
 int /*<<< orphan*/  IDS_MODE_RECORD ; 
 int /*<<< orphan*/  IDS_MODE_SEEK ; 
 int /*<<< orphan*/  IDS_MODE_STOP ; 
 int /*<<< orphan*/  IDS_MODE_UNKNOWN ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
#define  MCI_MODE_NOT_READY 134 
#define  MCI_MODE_OPEN 133 
#define  MCI_MODE_PAUSE 132 
#define  MCI_MODE_PLAY 131 
#define  MCI_MODE_RECORD 130 
#define  MCI_MODE_SEEK 129 
#define  MCI_MODE_STOP 128 
 int /*<<< orphan*/  SetWindowText (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringCbPrintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  hInstance ; 
 int /*<<< orphan*/ * szAppTitle ; 
 int /*<<< orphan*/  szCurrentFile ; 
 scalar_t__ wDeviceId ; 

void UpdateWindowCaption(HWND hwnd)
{
    TCHAR szNewTitle[MAX_PATH + 3 + 256];
    TCHAR szStatus[128];

    if (wDeviceId == 0)
    {
        SetWindowText(hwnd, szAppTitle);
        return;
    }

    switch (GetDeviceMode(hwnd))
    {
        case MCI_MODE_PAUSE:
        {
            LoadString(hInstance, IDS_MODE_PAUSE, szStatus, ARRAYSIZE(szStatus));
            break;
        }

        case MCI_MODE_STOP:
        {
            LoadString(hInstance, IDS_MODE_STOP, szStatus, ARRAYSIZE(szStatus));
            break;
        }

        case MCI_MODE_PLAY:
        {
            LoadString(hInstance, IDS_MODE_PLAY, szStatus, ARRAYSIZE(szStatus));
            break;
        }

        case MCI_MODE_OPEN:
        {
            LoadString(hInstance, IDS_MODE_OPEN, szStatus, ARRAYSIZE(szStatus));
            break;
        }

        case MCI_MODE_RECORD:
        {
            LoadString(hInstance, IDS_MODE_RECORD, szStatus, ARRAYSIZE(szStatus));
            break;
        }

        case MCI_MODE_SEEK:
        {
            LoadString(hInstance, IDS_MODE_SEEK, szStatus, ARRAYSIZE(szStatus));
            break;
        }

        case MCI_MODE_NOT_READY:
        {
            LoadString(hInstance, IDS_MODE_NOT_READY, szStatus, ARRAYSIZE(szStatus));
            break;
        }

        default:
        {
            LoadString(hInstance, IDS_MODE_UNKNOWN, szStatus, ARRAYSIZE(szStatus));
        }
    }

    StringCbPrintf(szNewTitle, sizeof(szNewTitle), _T("%s - %s (%s)"), szAppTitle, szCurrentFile, szStatus);
    SetWindowText(hwnd, szNewTitle);
}