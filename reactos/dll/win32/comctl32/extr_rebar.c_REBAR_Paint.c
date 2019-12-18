#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ fErase; int /*<<< orphan*/  rcPaint; } ;
struct TYPE_8__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ PAINTSTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ HDC ;

/* Variables and functions */
 scalar_t__ BeginPaint (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  REBAR_EraseBkGnd (TYPE_1__ const*,scalar_t__) ; 
 int /*<<< orphan*/  REBAR_Refresh (TYPE_1__ const*,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
REBAR_Paint (const REBAR_INFO *infoPtr, HDC hdc)
{
    if (hdc) {
        TRACE("painting\n");
#ifdef __REACTOS__
        REBAR_EraseBkGnd (infoPtr, hdc);
#endif
        REBAR_Refresh (infoPtr, hdc);
    } else {
        PAINTSTRUCT ps;
        hdc = BeginPaint (infoPtr->hwndSelf, &ps);
        TRACE("painting (%s)\n", wine_dbgstr_rect(&ps.rcPaint));
        if (ps.fErase) {
            /* Erase area of paint if requested */
            REBAR_EraseBkGnd (infoPtr, hdc);
        }
        REBAR_Refresh (infoPtr, hdc);
	EndPaint (infoPtr->hwndSelf, &ps);
    }

    return 0;
}