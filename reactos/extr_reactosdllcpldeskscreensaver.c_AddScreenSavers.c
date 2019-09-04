#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int ScreenSaverCount; TYPE_1__* ScreenSaverItems; } ;
struct TYPE_5__ {scalar_t__ szDisplayName; int /*<<< orphan*/  bIsScreenSaver; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ ScreenSaverItem ;
typedef  TYPE_2__* PDATA ;
typedef  char* LPTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_SETITEMDATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleFileName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetSystemDirectory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetWindowsDirectory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IDC_SCREENS_LIST ; 
 int /*<<< orphan*/  IDS_NONE ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SearchScreenSavers (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char) ; 
 scalar_t__ _tcsicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* _tcsrchr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hApplet ; 

__attribute__((used)) static VOID
AddScreenSavers(HWND hwndDlg, PDATA pData)
{
    HWND hwndScreenSavers = GetDlgItem(hwndDlg, IDC_SCREENS_LIST);
    TCHAR szSearchPath[MAX_PATH];
    TCHAR szLocalPath[MAX_PATH];
    INT i;
    ScreenSaverItem *ScreenSaverItem = NULL;
    LPTSTR lpBackSlash;

    /* Add the "None" item */
    ScreenSaverItem = pData->ScreenSaverItems;

    ScreenSaverItem->bIsScreenSaver = FALSE;

    LoadString(hApplet,
               IDS_NONE,
               ScreenSaverItem->szDisplayName,
               sizeof(ScreenSaverItem->szDisplayName) / sizeof(TCHAR));

    i = SendMessage(hwndScreenSavers,
                    CB_ADDSTRING,
                    0,
                    (LPARAM)ScreenSaverItem->szDisplayName);

    SendMessage(hwndScreenSavers,
                CB_SETITEMDATA,
                i,
                (LPARAM)0);

    // Initialize number of items into the list
    pData->ScreenSaverCount = 1;

    // Add all the screensavers where the applet is stored.
    GetModuleFileName(hApplet, szLocalPath, MAX_PATH);
    lpBackSlash = _tcsrchr(szLocalPath, _T('\\'));
    if (lpBackSlash != NULL)
    {
        *lpBackSlash = '\0';
        SearchScreenSavers(hwndScreenSavers, szLocalPath, pData);
    }

    // Add all the screensavers in the C:\ReactOS\System32 directory.
    GetSystemDirectory(szSearchPath, MAX_PATH);
    if (lpBackSlash != NULL && _tcsicmp(szSearchPath, szLocalPath) != 0)
        SearchScreenSavers(hwndScreenSavers, szSearchPath, pData);

    // Add all the screensavers in the C:\ReactOS directory.
    GetWindowsDirectory(szSearchPath, MAX_PATH);
    if (lpBackSlash != NULL && _tcsicmp(szSearchPath, szLocalPath) != 0)
        SearchScreenSavers(hwndScreenSavers, szSearchPath, pData);
}