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
struct ra_swapchain {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (TYPE_1__*) ; 
 int /*<<< orphan*/  qpc_to_us (struct ra_swapchain*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t qpc_us_now(struct ra_swapchain *sw)
{
    LARGE_INTEGER perf_count;
    QueryPerformanceCounter(&perf_count);
    return qpc_to_us(sw, perf_count.QuadPart);
}