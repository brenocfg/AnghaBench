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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ AllocAndLoadString (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SERVCON_INFO ; 
 int /*<<< orphan*/  IDC_SERVCON_NAME ; 
 int /*<<< orphan*/  IDC_SERVCON_PROGRESS ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  PBM_SETPOS ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static VOID
ResetProgressDialog(HWND hDlg,
                    LPWSTR ServiceName,
                    ULONG LabelId)
{
    LPWSTR lpProgStr;

    /* Load the label Id */
    if (AllocAndLoadString(&lpProgStr,
                           hInstance,
                           LabelId))
    {
        /* Write it to the dialog */
        SendDlgItemMessageW(hDlg,
                            IDC_SERVCON_INFO,
                            WM_SETTEXT,
                            0,
                            (LPARAM)lpProgStr);

        LocalFree(lpProgStr);
    }

    /* Write the service name to the dialog */
    SendDlgItemMessageW(hDlg,
                        IDC_SERVCON_NAME,
                        WM_SETTEXT,
                        0,
                        (LPARAM)ServiceName);

    /* Set the progress bar to the start */
    SendDlgItemMessageW(hDlg,
                        IDC_SERVCON_PROGRESS,
                        PBM_SETPOS,
                        0,
                        0);
}