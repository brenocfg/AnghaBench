#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t current_tab; TYPE_1__* tabs; int /*<<< orphan*/  hwndTabCtrl; } ;
struct TYPE_3__ {int id; scalar_t__ hwnd; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ HHInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int TAB_NUMTABS ; 
 int /*<<< orphan*/  TCM_GETCURSEL ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT OnTabChange(HWND hwnd)
{
    HHInfo *info = (HHInfo*)GetWindowLongPtrW(hwnd, 0);
    int tab_id, tab_index, i;

    TRACE("%p\n", hwnd);

    if (!info)
        return 0;

    if(info->tabs[info->current_tab].hwnd)
        ShowWindow(info->tabs[info->current_tab].hwnd, SW_HIDE);

    tab_id = (int) SendMessageW(info->hwndTabCtrl, TCM_GETCURSEL, 0, 0);
    /* convert the ID of the tab to an index in our tab list */
    tab_index = -1;
    for (i=0; i<TAB_NUMTABS; i++)
    {
        if (info->tabs[i].id == tab_id)
        {
            tab_index = i;
            break;
        }
    }
    if (tab_index == -1)
    {
        FIXME("Tab ID %d does not correspond to a valid index in the tab list.\n", tab_id);
        return 0;
    }
    info->current_tab = tab_index;

    if(info->tabs[info->current_tab].hwnd)
        ShowWindow(info->tabs[info->current_tab].hwnd, SW_SHOW);

    return 0;
}