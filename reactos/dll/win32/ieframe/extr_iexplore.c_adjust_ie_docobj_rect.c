#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ top; scalar_t__ bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_BROWSE_REBAR ; 
 int /*<<< orphan*/  IDC_BROWSE_STATUSBAR ; 
 int /*<<< orphan*/  InflateRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_GETBARHEIGHT ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adjust_ie_docobj_rect(HWND frame, RECT* rc)
{
    HWND hwndRebar = GetDlgItem(frame, IDC_BROWSE_REBAR);
    HWND hwndStatus = GetDlgItem(frame, IDC_BROWSE_STATUSBAR);
    INT barHeight = SendMessageW(hwndRebar, RB_GETBARHEIGHT, 0, 0);

    InflateRect(rc, 0, -barHeight);

    if(IsWindowVisible(hwndStatus))
    {
        RECT statusrc;

        GetClientRect(hwndStatus, &statusrc);
        rc->bottom -= statusrc.bottom - statusrc.top;
    }
}