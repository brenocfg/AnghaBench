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
struct ubifs_lpt_heap {int cnt; struct ubifs_lprops** arr; } ;
struct ubifs_lprops {int /*<<< orphan*/  flags; int /*<<< orphan*/  dirty; int /*<<< orphan*/  free; int /*<<< orphan*/  hpos; int /*<<< orphan*/  lnum; } ;
struct ubifs_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

void ubifs_dump_heap(struct ubifs_info *c, struct ubifs_lpt_heap *heap, int cat)
{
	int i;

	pr_err("(pid %d) start dumping heap cat %d (%d elements)\n",
	       current->pid, cat, heap->cnt);
	for (i = 0; i < heap->cnt; i++) {
		struct ubifs_lprops *lprops = heap->arr[i];

		pr_err("\t%d. LEB %d hpos %d free %d dirty %d flags %d\n",
		       i, lprops->lnum, lprops->hpos, lprops->free,
		       lprops->dirty, lprops->flags);
	}
	pr_err("(pid %d) finish dumping heap\n", current->pid);
}