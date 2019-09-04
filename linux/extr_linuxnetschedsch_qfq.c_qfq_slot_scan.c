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
struct qfq_group {unsigned int full_slots; unsigned int front; int /*<<< orphan*/  index; } ;
struct qfq_aggregate {int dummy; } ;

/* Variables and functions */
 unsigned int QFQ_MAX_SLOTS ; 
 unsigned int __ffs (unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct qfq_aggregate* qfq_slot_head (struct qfq_group*) ; 

__attribute__((used)) static struct qfq_aggregate *qfq_slot_scan(struct qfq_group *grp)
{
	unsigned int i;

	pr_debug("qfq slot_scan: grp %u full %#lx\n",
		 grp->index, grp->full_slots);

	if (grp->full_slots == 0)
		return NULL;

	i = __ffs(grp->full_slots);  /* zero based */
	if (i > 0) {
		grp->front = (grp->front + i) % QFQ_MAX_SLOTS;
		grp->full_slots >>= i;
	}

	return qfq_slot_head(grp);
}