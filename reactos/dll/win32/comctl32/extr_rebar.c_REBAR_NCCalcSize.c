#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dwStyle; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_6__ {scalar_t__ left; scalar_t__ right; scalar_t__ top; scalar_t__ bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ REBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HTHEME ;

/* Variables and functions */
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXEDGE ; 
 int /*<<< orphan*/  SM_CYEDGE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int WS_BORDER ; 
 void* max (scalar_t__,scalar_t__) ; 
 void* min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static inline LRESULT
REBAR_NCCalcSize (const REBAR_INFO *infoPtr, RECT *rect)
{
    HTHEME theme;

    if (infoPtr->dwStyle & WS_BORDER) {
        rect->left   = min(rect->left + GetSystemMetrics(SM_CXEDGE), rect->right);
        rect->right  = max(rect->right - GetSystemMetrics(SM_CXEDGE), rect->left);
        rect->top    = min(rect->top + GetSystemMetrics(SM_CYEDGE), rect->bottom);
        rect->bottom = max(rect->bottom - GetSystemMetrics(SM_CYEDGE), rect->top);
    }
    else if ((theme = GetWindowTheme (infoPtr->hwndSelf)))
    {
        /* FIXME: should use GetThemeInt */
#ifdef __REACTOS__
        rect->top = (rect->top + 1 < rect->bottom) ? rect->top : rect->bottom;
#else
        rect->top = min(rect->top + 1, rect->bottom);
#endif
    }
    TRACE("new client=(%s)\n", wine_dbgstr_rect(rect));
    return 0;
}