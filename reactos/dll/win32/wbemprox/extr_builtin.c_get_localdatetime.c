#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_6__ {int wMilliseconds; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
struct TYPE_5__ {scalar_t__ StandardBias; scalar_t__ DaylightBias; int /*<<< orphan*/  Bias; } ;
typedef  TYPE_1__ TIME_ZONE_INFORMATION ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  LONG ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocalTime (TYPE_2__*) ; 
 scalar_t__ GetTimeZoneInformation (TYPE_1__*) ; 
 scalar_t__ TIME_ZONE_ID_DAYLIGHT ; 
 scalar_t__ TIME_ZONE_ID_INVALID ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *get_localdatetime(void)
{
    static const WCHAR fmtW[] =
        {'%','0','4','u','%','0','2','u','%','0','2','u','%','0','2','u','%','0','2','u','%','0','2','u',
         '.','%','0','6','u','%','+','0','3','d',0};
    TIME_ZONE_INFORMATION tzi;
    SYSTEMTIME st;
    WCHAR *ret;
    DWORD Status;
    LONG Bias;

    Status = GetTimeZoneInformation(&tzi);

    if(Status == TIME_ZONE_ID_INVALID) return NULL;
    Bias = tzi.Bias;
    if(Status == TIME_ZONE_ID_DAYLIGHT)
        Bias+= tzi.DaylightBias;
    else
        Bias+= tzi.StandardBias;
    if (!(ret = heap_alloc( 26 * sizeof(WCHAR) ))) return NULL;

    GetLocalTime(&st);
    sprintfW( ret, fmtW, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds * 1000, -Bias);
    return ret;
}