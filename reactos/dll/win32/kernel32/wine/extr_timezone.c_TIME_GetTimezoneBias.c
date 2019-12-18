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
struct TYPE_4__ {scalar_t__ StandardBias; scalar_t__ DaylightBias; int /*<<< orphan*/  Bias; } ;
typedef  TYPE_1__ TIME_ZONE_INFORMATION ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TIME_CompTimeZoneID (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TIME_ZONE_ID_DAYLIGHT ; 
 scalar_t__ TIME_ZONE_ID_INVALID ; 
 scalar_t__ TIME_ZONE_ID_STANDARD ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
TIME_GetTimezoneBias(const TIME_ZONE_INFORMATION *pTZinfo, FILETIME *lpFileTime, BOOL islocal, LONG *pBias)
{
    LONG bias = pTZinfo->Bias;
    DWORD tzid = TIME_CompTimeZoneID(pTZinfo, lpFileTime, islocal);

    if( tzid == TIME_ZONE_ID_INVALID)
        return FALSE;
    if (tzid == TIME_ZONE_ID_DAYLIGHT)
        bias += pTZinfo->DaylightBias;
    else if (tzid == TIME_ZONE_ID_STANDARD)
        bias += pTZinfo->StandardBias;
    *pBias = bias;
    return TRUE;
}