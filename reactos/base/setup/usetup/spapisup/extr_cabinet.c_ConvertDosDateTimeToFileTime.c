#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_7__ {scalar_t__ Year; int /*<<< orphan*/  Month; int /*<<< orphan*/  Day; } ;
struct TYPE_6__ {int /*<<< orphan*/  Hour; int /*<<< orphan*/  Minute; int /*<<< orphan*/  Second; } ;
struct TYPE_5__ {scalar_t__ wYear; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wSecond; scalar_t__ wMilliseconds; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  TYPE_2__* PDOSTIME ;
typedef  TYPE_3__* PDOSDATE ;
typedef  int /*<<< orphan*/ * LPFILETIME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertSystemTimeToFileTime (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
ConvertDosDateTimeToFileTime(WORD wFatDate,
                             WORD wFatTime,
                             LPFILETIME lpFileTime)
{
    PDOSTIME pdtime = (PDOSTIME)&wFatTime;
    PDOSDATE pddate = (PDOSDATE)&wFatDate;
    SYSTEMTIME SystemTime;

    if (lpFileTime == NULL)
        return FALSE;

    SystemTime.wMilliseconds = 0;
    SystemTime.wSecond = pdtime->Second;
    SystemTime.wMinute = pdtime->Minute;
    SystemTime.wHour = pdtime->Hour;

    SystemTime.wDay = pddate->Day;
    SystemTime.wMonth = pddate->Month;
    SystemTime.wYear = 1980 + pddate->Year;

    ConvertSystemTimeToFileTime(&SystemTime, lpFileTime);

    return TRUE;
}