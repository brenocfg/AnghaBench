#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  clock_t ;
typedef  int __int64 ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemTime (int /*<<< orphan*/ *) ; 
 scalar_t__ SystemTimeToFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

clock_t wceex_clock()
{
    __int64 ticks;
    SYSTEMTIME stCurrent;
    FILETIME   ftCurrent;
    
    GetSystemTime(&stCurrent);
    
    if (SystemTimeToFileTime(&stCurrent, &ftCurrent))
    {
        ticks = *(__int64*)&ftCurrent;
    }
    else
    {
        /* The processor time used is not available or
         * its value cannot be represented.
         */
        ticks = -1;
    }
 
   return (clock_t)ticks;
}