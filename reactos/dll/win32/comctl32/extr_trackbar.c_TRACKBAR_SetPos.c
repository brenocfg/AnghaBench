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
struct TYPE_5__ {scalar_t__ lPos; scalar_t__ lRangeMin; scalar_t__ lRangeMax; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACKBAR_InvalidateThumbMove (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRACKBAR_UpdateThumb (TYPE_1__*) ; 

__attribute__((used)) static inline LRESULT
TRACKBAR_SetPos (TRACKBAR_INFO *infoPtr, BOOL fPosition, LONG lPosition)
{
    LONG oldPos = infoPtr->lPos;
    infoPtr->lPos = lPosition;

    if (infoPtr->lPos < infoPtr->lRangeMin)
	infoPtr->lPos = infoPtr->lRangeMin;

    if (infoPtr->lPos > infoPtr->lRangeMax)
	infoPtr->lPos = infoPtr->lRangeMax;

    if (fPosition && oldPos != lPosition)
    {
        TRACKBAR_UpdateThumb(infoPtr);
        TRACKBAR_InvalidateThumbMove(infoPtr, oldPos, lPosition);
    }

    return 0;
}