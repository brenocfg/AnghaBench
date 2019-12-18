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
struct TYPE_3__ {int dwStyle; int /*<<< orphan*/  uView; } ;
typedef  TYPE_1__ LISTVIEW_INFO ;

/* Variables and functions */
#define  LVS_ICON 131 
#define  LVS_LIST 130 
#define  LVS_REPORT 129 
#define  LVS_SMALLICON 128 
 int LVS_TYPEMASK ; 
 int /*<<< orphan*/  LV_VIEW_DETAILS ; 
 int /*<<< orphan*/  LV_VIEW_ICON ; 
 int /*<<< orphan*/  LV_VIEW_LIST ; 
 int /*<<< orphan*/  LV_VIEW_SMALLICON ; 

__attribute__((used)) static inline void map_style_view(LISTVIEW_INFO *infoPtr)
{
    switch (infoPtr->dwStyle & LVS_TYPEMASK)
    {
    case LVS_ICON:
        infoPtr->uView = LV_VIEW_ICON;
        break;
    case LVS_REPORT:
        infoPtr->uView = LV_VIEW_DETAILS;
        break;
    case LVS_SMALLICON:
        infoPtr->uView = LV_VIEW_SMALLICON;
        break;
    case LVS_LIST:
        infoPtr->uView = LV_VIEW_LIST;
    }
}