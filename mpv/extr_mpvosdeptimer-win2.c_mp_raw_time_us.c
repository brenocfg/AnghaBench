#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int QuadPart; } ;
struct TYPE_4__ {int QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (TYPE_1__*) ; 
 TYPE_2__ perf_freq ; 

uint64_t mp_raw_time_us(void)
{
    LARGE_INTEGER perf_count;
    QueryPerformanceCounter(&perf_count);

    // Convert QPC units (1/perf_freq seconds) to microseconds. This will work
    // without overflow because the QPC value is guaranteed not to roll-over
    // within 100 years, so perf_freq must be less than 2.9*10^9.
    return perf_count.QuadPart / perf_freq.QuadPart * 1000000 +
        perf_count.QuadPart % perf_freq.QuadPart * 1000000 / perf_freq.QuadPart;
}