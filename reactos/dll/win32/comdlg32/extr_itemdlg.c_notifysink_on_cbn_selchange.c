#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ customctrl ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  FileDialogImpl ;

/* Variables and functions */
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cctrl_event_OnItemSelected (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_cctrl_from_dlgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT notifysink_on_cbn_selchange(FileDialogImpl *This, HWND hwnd, WPARAM wparam)
{
    customctrl *ctrl = get_cctrl_from_dlgid(This, LOWORD(wparam));
    TRACE("%p, %p (%lx)\n", This, ctrl, wparam);

    if(ctrl)
    {
        UINT index = SendMessageW(ctrl->hwnd, CB_GETCURSEL, 0, 0);
        UINT selid = SendMessageW(ctrl->hwnd, CB_GETITEMDATA, index, 0);

        cctrl_event_OnItemSelected(This, ctrl->id, selid);
    }
    return TRUE;
}