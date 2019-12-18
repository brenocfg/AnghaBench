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
struct ubifs_lpt_heap {int cnt; struct ubifs_lprops** arr; } ;
struct ubifs_lprops {int hpos; } ;
struct ubifs_info {struct ubifs_lpt_heap* lpt_heap; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_lpt_heap (struct ubifs_info*,struct ubifs_lpt_heap*,struct ubifs_lprops*,int,int) ; 
 int /*<<< orphan*/  dbg_check_heap (struct ubifs_info*,struct ubifs_lpt_heap*,int,int) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 

__attribute__((used)) static void remove_from_lpt_heap(struct ubifs_info *c,
				 struct ubifs_lprops *lprops, int cat)
{
	struct ubifs_lpt_heap *heap;
	int hpos = lprops->hpos;

	heap = &c->lpt_heap[cat - 1];
	ubifs_assert(c, hpos >= 0 && hpos < heap->cnt);
	ubifs_assert(c, heap->arr[hpos] == lprops);
	heap->cnt -= 1;
	if (hpos < heap->cnt) {
		heap->arr[hpos] = heap->arr[heap->cnt];
		heap->arr[hpos]->hpos = hpos;
		adjust_lpt_heap(c, heap, heap->arr[hpos], hpos, cat);
	}
	dbg_check_heap(c, heap, cat, -1);
}