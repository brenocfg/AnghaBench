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
typedef  size_t u32 ;
struct events_stats {int /*<<< orphan*/ * nr_events; } ;

/* Variables and functions */

void events_stats__inc(struct events_stats *stats, u32 type)
{
	++stats->nr_events[0];
	++stats->nr_events[type];
}