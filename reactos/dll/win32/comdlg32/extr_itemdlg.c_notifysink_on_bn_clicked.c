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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  id; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ customctrl ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  FileDialogImpl ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BM_GETCHECK ; 
 scalar_t__ BST_CHECKED ; 
 scalar_t__ IDLG_CCTRL_CHECKBUTTON ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cctrl_event_OnButtonClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cctrl_event_OnCheckButtonToggled (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* get_cctrl_from_dlgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT notifysink_on_bn_clicked(FileDialogImpl *This, HWND hwnd, WPARAM wparam)
{
    customctrl *ctrl = get_cctrl_from_dlgid(This, LOWORD(wparam));

    TRACE("%p, %lx\n", This, wparam);

    if(ctrl)
    {
        if(ctrl->type == IDLG_CCTRL_CHECKBUTTON)
        {
            BOOL checked = (SendMessageW(ctrl->hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED);
            cctrl_event_OnCheckButtonToggled(This, ctrl->id, checked);
        }
        else
            cctrl_event_OnButtonClicked(This, ctrl->id);
    }

    return TRUE;
}