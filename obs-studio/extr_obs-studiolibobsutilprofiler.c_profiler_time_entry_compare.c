#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ time_delta; } ;
typedef  TYPE_1__ profiler_time_entry ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */

__attribute__((used)) static int profiler_time_entry_compare(const void *first, const void *second)
{
	int64_t diff = ((profiler_time_entry*)second)->time_delta -
		((profiler_time_entry*)first)->time_delta;
	return diff < 0 ? -1 : (diff > 0 ? 1 : 0);
}