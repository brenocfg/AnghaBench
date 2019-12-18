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
struct TYPE_3__ {int /*<<< orphan*/  hMonthCal; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int DWORD ;
typedef  TYPE_1__ DATETIME_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GDTR_MAX ; 
 int GDTR_MIN ; 
 int /*<<< orphan*/  MCM_GETRANGE ; 
 int MONTHCAL_CompareSystemTime (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  max_allowed_date ; 
 int /*<<< orphan*/  min_allowed_date ; 

__attribute__((used)) static BOOL DATETIME_IsDateInValidRange(const DATETIME_INFO *infoPtr, const SYSTEMTIME *date)
{
    SYSTEMTIME range[2];
    DWORD limits;

    if ((MONTHCAL_CompareSystemTime(date, &max_allowed_date) == 1) ||
        (MONTHCAL_CompareSystemTime(date, &min_allowed_date) == -1))
        return FALSE;

    limits = SendMessageW (infoPtr->hMonthCal, MCM_GETRANGE, 0, (LPARAM)range);

    if (limits & GDTR_MAX)
    {
        if (MONTHCAL_CompareSystemTime(date, &range[1]) == 1)
           return FALSE;
    }

    if (limits & GDTR_MIN)
    {
        if (MONTHCAL_CompareSystemTime(date, &range[0]) == -1)
           return FALSE;
    }

    return TRUE;
}