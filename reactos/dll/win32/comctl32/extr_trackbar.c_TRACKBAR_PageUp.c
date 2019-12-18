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
struct TYPE_4__ {scalar_t__ lPos; scalar_t__ lRangeMin; scalar_t__ lPageSize; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  TB_PAGEUP ; 
 int /*<<< orphan*/  notify_with_scroll (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
TRACKBAR_PageUp (TRACKBAR_INFO *infoPtr)
{
    if (infoPtr->lPos == infoPtr->lRangeMin) return;

    infoPtr->lPos -= infoPtr->lPageSize;
    if (infoPtr->lPos < infoPtr->lRangeMin)
        infoPtr->lPos = infoPtr->lRangeMin;
    notify_with_scroll (infoPtr, TB_PAGEUP);
}