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
struct TYPE_3__ {int /*<<< orphan*/  stateMask; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ LVITEMW ;
typedef  int /*<<< orphan*/  LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  INDEXTOSTATEIMAGEMASK (int) ; 
 int /*<<< orphan*/  LISTVIEW_GetItemState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTVIEW_SetItemState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LVIS_STATEIMAGEMASK ; 
 int STATEIMAGEINDEX (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toggle_checkbox_state(LISTVIEW_INFO *infoPtr, INT nItem)
{
    DWORD state = STATEIMAGEINDEX(LISTVIEW_GetItemState(infoPtr, nItem, LVIS_STATEIMAGEMASK));
    if(state == 1 || state == 2)
    {
        LVITEMW lvitem;
        state ^= 3;
        lvitem.state = INDEXTOSTATEIMAGEMASK(state);
        lvitem.stateMask = LVIS_STATEIMAGEMASK;
        LISTVIEW_SetItemState(infoPtr, nItem, &lvitem);
    }
}