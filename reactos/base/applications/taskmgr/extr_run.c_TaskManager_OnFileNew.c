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
typedef  int /*<<< orphan*/  szTitle ;
typedef  int /*<<< orphan*/  szText ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  (* RUNFILEDLG ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  HICON ;
typedef  scalar_t__ FARPROC ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDI_TASKMANAGER ; 
 int /*<<< orphan*/  IDS_CREATENEWTASK ; 
 int /*<<< orphan*/  IDS_CREATENEWTASK_DESC ; 
 int /*<<< orphan*/  LoadIconW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadLibraryW (char*) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFF_CALCDIRECTORY ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hMainWnd ; 

void TaskManager_OnFileNew(void)
{
    HMODULE     hShell32;
    RUNFILEDLG  RunFileDlg;
    WCHAR       szTitle[40];
    WCHAR       szText[256];

    /* Load language strings from resource file */
    LoadStringW(hInst, IDS_CREATENEWTASK, szTitle, sizeof(szTitle) / sizeof(szTitle[0]));
    LoadStringW(hInst, IDS_CREATENEWTASK_DESC, szText, sizeof(szText) / sizeof(szText[0]));

    hShell32 = LoadLibraryW(L"SHELL32.DLL");
    RunFileDlg = (RUNFILEDLG)(FARPROC)GetProcAddress(hShell32, (LPCSTR)61);

    /* Show "Run..." dialog */
    if (RunFileDlg)
    {
        HICON hIcon = LoadIconW(hInst, MAKEINTRESOURCEW(IDI_TASKMANAGER));

        /* NOTE - don't check whether running on win 9x or NT, let's just
                  assume that a unicode build only runs on NT */
        RunFileDlg(hMainWnd, hIcon, NULL, szTitle, szText, RFF_CALCDIRECTORY);

        DeleteObject(hIcon);
    }

    FreeLibrary(hShell32);
}