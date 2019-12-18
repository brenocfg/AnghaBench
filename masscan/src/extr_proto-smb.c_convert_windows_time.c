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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 scalar_t__ EPOCH_DIFFERENCE ; 
 long long TICKS_PER_SECOND ; 

__attribute__((used)) static time_t
convert_windows_time(long long int filetime)
{
    unsigned long long seconds = filetime / TICKS_PER_SECOND;
    seconds -= EPOCH_DIFFERENCE;
    return (time_t)seconds;
}