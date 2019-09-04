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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  max_time; } ;
typedef  TYPE_1__ profiler_snapshot_entry_t ;

/* Variables and functions */

uint64_t profiler_snapshot_entry_max_time(profiler_snapshot_entry_t *entry)
{
	return entry ? entry->max_time : 0;
}