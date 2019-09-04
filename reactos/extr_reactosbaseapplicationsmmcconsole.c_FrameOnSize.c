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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwndMDIClient ; 

__attribute__((used)) static VOID
FrameOnSize(HWND hMainWnd,
            WORD cx,
            WORD cy)
{
    RECT rcClient; //, rcTool, rcStatus;
//    int lvHeight, iToolHeight, iStatusHeight;

    /* Size toolbar and get height */
//    SendMessage(Info->hTool, TB_AUTOSIZE, 0, 0);
//    GetWindowRect(Info->hTool, &rcTool);
//    iToolHeight = rcTool.bottom - rcTool.top;

    /* Size status bar and get height */
//    SendMessage(Info->hStatus, WM_SIZE, 0, 0);
//    GetWindowRect(Info->hStatus, &rcStatus);
//    iStatusHeight = rcStatus.bottom - rcStatus.top;

    /* Calculate remaining height and size list view */
    GetClientRect(hMainWnd, &rcClient);
//    lvHeight = rcClient.bottom - iToolHeight - iStatusHeight;
    SetWindowPos(hwndMDIClient, //Info->hTreeView,
                 NULL,
                 0,
                 0, //iToolHeight,
                 rcClient.right,
                 rcClient.bottom, //lvHeight,
                 SWP_NOZORDER);
}