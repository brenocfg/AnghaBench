#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ lRangeMin; scalar_t__ lPos; int lPageSize; int lRangeMax; int dwStyle; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LONG ;
typedef  int BOOL ;

/* Variables and functions */
 int TBS_AUTOTICKS ; 
 int /*<<< orphan*/  TB_THUMBPOSCHANGED ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateAll (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_RecalculateTics (TYPE_1__*) ; 

__attribute__((used)) static inline LRESULT
TRACKBAR_SetRangeMin (TRACKBAR_INFO *infoPtr, BOOL redraw, LONG lMin)
{
    BOOL changed = infoPtr->lRangeMin != lMin;

    infoPtr->lRangeMin = lMin;
    if (infoPtr->lPos < infoPtr->lRangeMin) {
        infoPtr->lPos = infoPtr->lRangeMin;
        infoPtr->flags |= TB_THUMBPOSCHANGED;
    }

    infoPtr->lPageSize = (infoPtr->lRangeMax - infoPtr->lRangeMin) / 5;
    if (infoPtr->lPageSize == 0) infoPtr->lPageSize = 1;

    if (changed && (infoPtr->dwStyle & TBS_AUTOTICKS))
        TRACKBAR_RecalculateTics (infoPtr);

    if (redraw) TRACKBAR_InvalidateAll(infoPtr);

    return 0;
}