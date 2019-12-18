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
typedef  scalar_t__ WPARAM ;
struct TYPE_3__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ COMBOEX_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int RDW_ALLCHILDREN ; 
 int RDW_ERASE ; 
 int RDW_INVALIDATE ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WM_SETREDRAW ; 

__attribute__((used)) static LRESULT COMBOEX_SetRedraw(const COMBOEX_INFO *infoPtr, WPARAM wParam, LPARAM lParam)
{
    LRESULT ret = DefWindowProcW( infoPtr->hwndSelf, WM_SETREDRAW, wParam, lParam );
    if (wParam) RedrawWindow( infoPtr->hwndSelf, NULL, 0, RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN );
    return ret;
}