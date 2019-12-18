#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int computed; int cycles; } ;
struct hist_entry {TYPE_1__* block_info; TYPE_2__ diff; } ;
struct TYPE_3__ {int cycles_aggr; int num_aggr; scalar_t__ num; } ;

/* Variables and functions */

__attribute__((used)) static void compute_cycles_diff(struct hist_entry *he,
				struct hist_entry *pair)
{
	pair->diff.computed = true;
	if (pair->block_info->num && he->block_info->num) {
		pair->diff.cycles =
			pair->block_info->cycles_aggr / pair->block_info->num_aggr -
			he->block_info->cycles_aggr / he->block_info->num_aggr;
	}
}