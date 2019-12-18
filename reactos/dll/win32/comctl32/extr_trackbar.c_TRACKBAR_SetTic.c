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
struct TYPE_5__ {scalar_t__ lRangeMin; scalar_t__ lRangeMax; int uNumTics; scalar_t__* tics; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NM_OUTOFMEMORY ; 
 scalar_t__* ReAlloc (scalar_t__*,int) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateAll (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  notify (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LRESULT
TRACKBAR_SetTic (TRACKBAR_INFO *infoPtr, LONG lPos)
{
    if ((lPos < infoPtr->lRangeMin) || (lPos> infoPtr->lRangeMax))
        return FALSE;

    TRACE("lPos=%d\n", lPos);

    infoPtr->uNumTics++;
    infoPtr->tics=ReAlloc( infoPtr->tics,
                                    (infoPtr->uNumTics)*sizeof (DWORD));
    if (!infoPtr->tics) {
	infoPtr->uNumTics = 0;
	notify(infoPtr, NM_OUTOFMEMORY);
	return FALSE;
    }
    infoPtr->tics[infoPtr->uNumTics-1] = lPos;

    TRACKBAR_InvalidateAll(infoPtr);

    return TRUE;
}