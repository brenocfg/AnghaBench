#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_5__ {int nTrackTool; int nTool; int uNumTools; int /*<<< orphan*/  hwndSelf; TYPE_1__* tools; scalar_t__ bTrackActive; } ;
struct TYPE_4__ {int uFlags; } ;
typedef  TYPE_2__ TOOLTIPS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTTRANSPARENT ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int TTF_TRANSPARENT ; 
 int /*<<< orphan*/  WM_NCHITTEST ; 

__attribute__((used)) static LRESULT
TOOLTIPS_NCHitTest (const TOOLTIPS_INFO *infoPtr, WPARAM wParam, LPARAM lParam)
{
    INT nTool = (infoPtr->bTrackActive) ? infoPtr->nTrackTool : infoPtr->nTool;

    TRACE(" nTool=%d\n", nTool);

    if ((nTool > -1) && (nTool < infoPtr->uNumTools)) {
	if (infoPtr->tools[nTool].uFlags & TTF_TRANSPARENT) {
	    TRACE("-- in transparent mode\n");
	    return HTTRANSPARENT;
	}
    }

    return DefWindowProcW (infoPtr->hwndSelf, WM_NCHITTEST, wParam, lParam);
}