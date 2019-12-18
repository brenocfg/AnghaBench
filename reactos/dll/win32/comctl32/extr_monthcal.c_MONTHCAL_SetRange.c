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
struct TYPE_3__ {int rangeValid; void* minDate; void* maxDate; int /*<<< orphan*/  todaysDate; } ;
typedef  void* SYSTEMTIME ;
typedef  int SHORT ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 scalar_t__ CompareFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int GDTR_MAX ; 
 int GDTR_MIN ; 
 int /*<<< orphan*/  MONTHCAL_CopyTime (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  MONTHCAL_ValidateDate (void**) ; 
 int /*<<< orphan*/  MONTHCAL_ValidateTime (void**) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int,void**) ; 
 int /*<<< orphan*/  TRUE ; 
 void* st_null ; 

__attribute__((used)) static LRESULT
MONTHCAL_SetRange(MONTHCAL_INFO *infoPtr, SHORT limits, SYSTEMTIME *range)
{
    FILETIME ft_min, ft_max;

    TRACE("%x %p\n", limits, range);

    if ((limits & GDTR_MIN && !MONTHCAL_ValidateDate(&range[0])) ||
        (limits & GDTR_MAX && !MONTHCAL_ValidateDate(&range[1])))
        return FALSE;

    infoPtr->rangeValid = 0;
    infoPtr->minDate = infoPtr->maxDate = st_null;

    if (limits & GDTR_MIN)
    {
        if (!MONTHCAL_ValidateTime(&range[0]))
            MONTHCAL_CopyTime(&infoPtr->todaysDate, &range[0]);

        infoPtr->minDate = range[0];
        infoPtr->rangeValid |= GDTR_MIN;
    }
    if (limits & GDTR_MAX)
    {
        if (!MONTHCAL_ValidateTime(&range[1]))
            MONTHCAL_CopyTime(&infoPtr->todaysDate, &range[1]);

        infoPtr->maxDate = range[1];
        infoPtr->rangeValid |= GDTR_MAX;
    }

    /* Only one limit set - we are done */
    if ((infoPtr->rangeValid & (GDTR_MIN | GDTR_MAX)) != (GDTR_MIN | GDTR_MAX))
        return TRUE;

    SystemTimeToFileTime(&infoPtr->maxDate, &ft_max);
    SystemTimeToFileTime(&infoPtr->minDate, &ft_min);

    if (CompareFileTime(&ft_min, &ft_max) >= 0)
    {
        if ((limits & (GDTR_MIN | GDTR_MAX)) == (GDTR_MIN | GDTR_MAX))
        {
            /* Native swaps limits only when both limits are being set. */
            SYSTEMTIME st_tmp = infoPtr->minDate;
            infoPtr->minDate  = infoPtr->maxDate;
            infoPtr->maxDate  = st_tmp;
        }
        else
        {
            /* reset the other limit */
            if (limits & GDTR_MIN) infoPtr->maxDate = st_null;
            if (limits & GDTR_MAX) infoPtr->minDate = st_null;
            infoPtr->rangeValid &= limits & GDTR_MIN ? ~GDTR_MAX : ~GDTR_MIN;
        }
    }

    return TRUE;
}