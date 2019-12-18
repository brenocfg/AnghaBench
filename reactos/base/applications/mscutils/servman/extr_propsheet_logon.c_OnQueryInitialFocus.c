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
struct TYPE_3__ {scalar_t__ bLocalSystem; } ;
typedef  TYPE_1__* PLOGONDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DWLP_MSGRESULT ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_LOGON_SYSTEMACCOUNT ; 
 int /*<<< orphan*/  IDC_LOGON_THISACCOUNT ; 
 int /*<<< orphan*/  SetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL
OnQueryInitialFocus(
    HWND hwndDlg,
    PLOGONDATA pLogonData)
{
    HWND hwnd = GetDlgItem(hwndDlg, pLogonData->bLocalSystem ? IDC_LOGON_SYSTEMACCOUNT : IDC_LOGON_THISACCOUNT);

    SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, (LPARAM)hwnd);

    return TRUE;
}