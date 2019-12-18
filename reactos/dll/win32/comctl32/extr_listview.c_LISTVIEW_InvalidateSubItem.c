#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ uView; int /*<<< orphan*/  nItemHeight; } ;
struct TYPE_16__ {scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_15__ {int /*<<< orphan*/  bottom; scalar_t__ top; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  TYPE_3__ LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  LISTVIEW_GetHeaderRect (TYPE_3__ const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LISTVIEW_GetItemOrigin (TYPE_3__ const*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  LISTVIEW_GetOrigin (TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  LISTVIEW_InvalidateRect (TYPE_3__ const*,TYPE_1__*) ; 
 scalar_t__ LV_VIEW_DETAILS ; 
 int /*<<< orphan*/  OffsetRect (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  is_redrawing (TYPE_3__ const*) ; 

__attribute__((used)) static inline void LISTVIEW_InvalidateSubItem(const LISTVIEW_INFO *infoPtr, INT nItem, INT nSubItem)
{
    POINT Origin, Position;
    RECT rcBox;
    
    if(!is_redrawing(infoPtr)) return; 
    assert (infoPtr->uView == LV_VIEW_DETAILS);
    LISTVIEW_GetOrigin(infoPtr, &Origin);
    LISTVIEW_GetItemOrigin(infoPtr, nItem, &Position);
    LISTVIEW_GetHeaderRect(infoPtr, nSubItem, &rcBox);
    rcBox.top = 0;
    rcBox.bottom = infoPtr->nItemHeight;
    OffsetRect(&rcBox, Origin.x, Origin.y + Position.y);
    LISTVIEW_InvalidateRect(infoPtr, &rcBox);
}