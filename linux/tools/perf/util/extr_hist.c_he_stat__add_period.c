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
typedef  scalar_t__ u64 ;
struct he_stat {int nr_events; int /*<<< orphan*/  weight; int /*<<< orphan*/  period; } ;

/* Variables and functions */

__attribute__((used)) static void he_stat__add_period(struct he_stat *he_stat, u64 period,
				u64 weight)
{

	he_stat->period		+= period;
	he_stat->weight		+= weight;
	he_stat->nr_events	+= 1;
}