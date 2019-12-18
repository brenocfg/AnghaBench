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
typedef  int /*<<< orphan*/  ti ;
typedef  char WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  liKeBootTime; } ;
struct TYPE_5__ {int Milliseconds; int /*<<< orphan*/  Second; int /*<<< orphan*/  Minute; int /*<<< orphan*/  Hour; int /*<<< orphan*/  Day; int /*<<< orphan*/  Month; int /*<<< orphan*/  Year; } ;
typedef  TYPE_1__ TIME_FIELDS ;
typedef  TYPE_2__ SYSTEM_TIMEOFDAY_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  NtQuerySystemInformation (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlTimeToTimeFields (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SystemTimeOfDayInformation ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static WCHAR *get_lastbootuptime(void)
{
    static const WCHAR fmtW[] =
        {'%','0','4','u','%','0','2','u','%','0','2','u','%','0','2','u','%','0','2','u','%','0','2','u',
         '.','%','0','6','u','+','0','0','0',0};
    SYSTEM_TIMEOFDAY_INFORMATION ti;
    TIME_FIELDS tf;
    WCHAR *ret;

    if (!(ret = heap_alloc( 26 * sizeof(WCHAR) ))) return NULL;

    NtQuerySystemInformation( SystemTimeOfDayInformation, &ti, sizeof(ti), NULL );
    RtlTimeToTimeFields( &ti.liKeBootTime, &tf );
    sprintfW( ret, fmtW, tf.Year, tf.Month, tf.Day, tf.Hour, tf.Minute, tf.Second, tf.Milliseconds * 1000 );
    return ret;
}