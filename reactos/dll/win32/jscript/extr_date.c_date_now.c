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
struct TYPE_3__ {int dwLowDateTime; scalar_t__ dwHighDateTime; } ;
typedef  int LONGLONG ;
typedef  TYPE_1__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_1__*) ; 
 double TIME_EPOCH ; 

__attribute__((used)) static double date_now(void)
{
    FILETIME ftime;
    LONGLONG time;

    GetSystemTimeAsFileTime(&ftime);
    time = ((LONGLONG)ftime.dwHighDateTime << 32) + ftime.dwLowDateTime;

    return time/10000 - TIME_EPOCH;
}