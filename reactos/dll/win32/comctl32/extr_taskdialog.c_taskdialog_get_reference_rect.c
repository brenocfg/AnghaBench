#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct taskdialog_template_desc {TYPE_1__* taskconfig; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_8__ {unsigned int left; unsigned int right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
struct TYPE_9__ {int cbSize; TYPE_2__ rcWork; } ;
struct TYPE_7__ {int dwFlags; scalar_t__ hwndParent; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ MONITORINFO ;
typedef  int /*<<< orphan*/  HMONITOR ;

/* Variables and functions */
 scalar_t__ GetActiveWindow () ; 
 int /*<<< orphan*/  GetMonitorInfoW (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GetWindowRect (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  MONITOR_DEFAULTTOPRIMARY ; 
 int /*<<< orphan*/  MonitorFromWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int TDF_POSITION_RELATIVE_TO_WINDOW ; 
 int /*<<< orphan*/  pixels_to_dialogunits (struct taskdialog_template_desc const*,unsigned int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int taskdialog_get_reference_rect(const struct taskdialog_template_desc *desc, RECT *ret)
{
    HMONITOR monitor = MonitorFromWindow(desc->taskconfig->hwndParent ? desc->taskconfig->hwndParent : GetActiveWindow(),
            MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO info;

    info.cbSize = sizeof(info);
    GetMonitorInfoW(monitor, &info);

    if (desc->taskconfig->dwFlags & TDF_POSITION_RELATIVE_TO_WINDOW && desc->taskconfig->hwndParent)
        GetWindowRect(desc->taskconfig->hwndParent, ret);
    else
        *ret = info.rcWork;

    pixels_to_dialogunits(desc, &ret->left, &ret->top);
    pixels_to_dialogunits(desc, &ret->right, &ret->bottom);

    pixels_to_dialogunits(desc, &info.rcWork.left, &info.rcWork.top);
    pixels_to_dialogunits(desc, &info.rcWork.right, &info.rcWork.bottom);
    return info.rcWork.right - info.rcWork.left;
}