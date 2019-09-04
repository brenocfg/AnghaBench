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
typedef  scalar_t__ u32 ;
struct gb_loopback_stats {scalar_t__ min; scalar_t__ max; int /*<<< orphan*/  count; int /*<<< orphan*/  sum; } ;

/* Variables and functions */

__attribute__((used)) static void gb_loopback_update_stats(struct gb_loopback_stats *stats, u32 val)
{
	if (stats->min > val)
		stats->min = val;
	if (stats->max < val)
		stats->max = val;
	stats->sum += val;
	stats->count++;
}