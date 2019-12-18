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
struct TYPE_4__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ LISTVIEW_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_redrawing (TYPE_1__ const*) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline void LISTVIEW_InvalidateRect(const LISTVIEW_INFO *infoPtr, const RECT* rect)
{
    if(!is_redrawing(infoPtr)) return; 
    TRACE(" invalidating rect=%s\n", wine_dbgstr_rect(rect));
    InvalidateRect(infoPtr->hwndSelf, rect, TRUE);
}