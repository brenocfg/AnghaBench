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
typedef  int /*<<< orphan*/  toolinfo ;
struct cred_dialog_params {int /*<<< orphan*/  fBalloonTipActive; int /*<<< orphan*/  hwndBalloonTip; } ;
struct TYPE_3__ {int cbSize; int uId; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TTTOOLINFOW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTM_TRACKACTIVATE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void CredDialogHideBalloonTip(HWND hwndDlg, struct cred_dialog_params *params)
{
    TTTOOLINFOW toolinfo;

    if (!params->hwndBalloonTip)
        return;

    memset(&toolinfo, 0, sizeof(toolinfo));

    toolinfo.cbSize = sizeof(toolinfo);
    toolinfo.hwnd = hwndDlg;
    toolinfo.uId = 0;
    SendMessageW(params->hwndBalloonTip, TTM_TRACKACTIVATE, FALSE, (LPARAM)&toolinfo);
    toolinfo.uId = 1;
    SendMessageW(params->hwndBalloonTip, TTM_TRACKACTIVATE, FALSE, (LPARAM)&toolinfo);

    params->fBalloonTipActive = FALSE;
}