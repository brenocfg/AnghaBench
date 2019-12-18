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
struct iterations {scalar_t__ cycles; int /*<<< orphan*/  nr_loop_iter; } ;
struct TYPE_2__ {scalar_t__ cycles; } ;
struct branch_entry {TYPE_1__ flags; } ;

/* Variables and functions */

__attribute__((used)) static void save_iterations(struct iterations *iter,
			    struct branch_entry *be, int nr)
{
	int i;

	iter->nr_loop_iter++;
	iter->cycles = 0;

	for (i = 0; i < nr; i++)
		iter->cycles += be[i].flags.cycles;
}