#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int right; int left; int bottom; int top; } ;
struct TYPE_7__ {int dwStyle; int uThumbLen; int /*<<< orphan*/  flags; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int TBS_ENABLESELRANGE ; 
 int TBS_VERT ; 
 int /*<<< orphan*/  TB_SELECTIONCHANGED ; 
 int /*<<< orphan*/  TRACKBAR_CalcChannel (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_UpdateThumb (TYPE_1__*) ; 

__attribute__((used)) static LRESULT
TRACKBAR_InitializeThumb (TRACKBAR_INFO *infoPtr)
{
    RECT rect;
    int clientWidth, clientMetric;

    /* initial thumb length */
    clientMetric = (infoPtr->dwStyle & TBS_ENABLESELRANGE) ? 23 : 21;
    GetClientRect(infoPtr->hwndSelf,&rect);
    if (infoPtr->dwStyle & TBS_VERT) {
	clientWidth = rect.right - rect.left;
    } else {
	clientWidth = rect.bottom - rect.top;
    }
    if (clientWidth >= clientMetric)
        infoPtr->uThumbLen = clientMetric;
    else
        infoPtr->uThumbLen = clientWidth > 9 ? clientWidth - 6 : 4;

    TRACKBAR_CalcChannel (infoPtr);
    TRACKBAR_UpdateThumb (infoPtr);
    infoPtr->flags &= ~TB_SELECTIONCHANGED;

    return 0;
}