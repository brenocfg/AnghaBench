#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WPARAM ;
struct TYPE_7__ {int bRedraw; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ TREEVIEW_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TREEVIEW_Invalidate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREEVIEW_RecalculateVisibleOrder (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREEVIEW_UpdateScrollBars (TYPE_1__*) ; 
 int /*<<< orphan*/  TREEVIEW_UpdateSubTree (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
TREEVIEW_SetRedraw(TREEVIEW_INFO* infoPtr, WPARAM wParam)
{
    infoPtr->bRedraw = wParam != 0;

    if (infoPtr->bRedraw)
    {
        TREEVIEW_UpdateSubTree(infoPtr, infoPtr->root);
        TREEVIEW_RecalculateVisibleOrder(infoPtr, NULL);
        TREEVIEW_UpdateScrollBars(infoPtr);
        TREEVIEW_Invalidate(infoPtr, NULL);
    }
    return 0;
}