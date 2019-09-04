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
typedef  int /*<<< orphan*/  u64 ;
struct cpudl {int size; TYPE_1__* elements; } ;
struct TYPE_2__ {int cpu; int idx; int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 scalar_t__ dl_time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int left_child (int) ; 
 int right_child (int) ; 

__attribute__((used)) static void cpudl_heapify_down(struct cpudl *cp, int idx)
{
	int l, r, largest;

	int orig_cpu = cp->elements[idx].cpu;
	u64 orig_dl = cp->elements[idx].dl;

	if (left_child(idx) >= cp->size)
		return;

	/* adapted from lib/prio_heap.c */
	while (1) {
		u64 largest_dl;

		l = left_child(idx);
		r = right_child(idx);
		largest = idx;
		largest_dl = orig_dl;

		if ((l < cp->size) && dl_time_before(orig_dl,
						cp->elements[l].dl)) {
			largest = l;
			largest_dl = cp->elements[l].dl;
		}
		if ((r < cp->size) && dl_time_before(largest_dl,
						cp->elements[r].dl))
			largest = r;

		if (largest == idx)
			break;

		/* pull largest child onto idx */
		cp->elements[idx].cpu = cp->elements[largest].cpu;
		cp->elements[idx].dl = cp->elements[largest].dl;
		cp->elements[cp->elements[idx].cpu].idx = idx;
		idx = largest;
	}
	/* actual push down of saved original values orig_* */
	cp->elements[idx].cpu = orig_cpu;
	cp->elements[idx].dl = orig_dl;
	cp->elements[cp->elements[idx].cpu].idx = idx;
}