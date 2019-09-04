#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xol_area {unsigned long vaddr; int /*<<< orphan*/  wq; int /*<<< orphan*/  slot_count; int /*<<< orphan*/  bitmap; } ;
struct task_struct {TYPE_3__* utask; TYPE_2__* mm; } ;
struct TYPE_6__ {unsigned long xol_vaddr; } ;
struct TYPE_4__ {struct xol_area* xol_area; } ;
struct TYPE_5__ {TYPE_1__ uprobes_state; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int UINSNS_PER_PAGE ; 
 unsigned long UPROBE_XOL_SLOT_BYTES ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xol_free_insn_slot(struct task_struct *tsk)
{
	struct xol_area *area;
	unsigned long vma_end;
	unsigned long slot_addr;

	if (!tsk->mm || !tsk->mm->uprobes_state.xol_area || !tsk->utask)
		return;

	slot_addr = tsk->utask->xol_vaddr;
	if (unlikely(!slot_addr))
		return;

	area = tsk->mm->uprobes_state.xol_area;
	vma_end = area->vaddr + PAGE_SIZE;
	if (area->vaddr <= slot_addr && slot_addr < vma_end) {
		unsigned long offset;
		int slot_nr;

		offset = slot_addr - area->vaddr;
		slot_nr = offset / UPROBE_XOL_SLOT_BYTES;
		if (slot_nr >= UINSNS_PER_PAGE)
			return;

		clear_bit(slot_nr, area->bitmap);
		atomic_dec(&area->slot_count);
		smp_mb__after_atomic(); /* pairs with prepare_to_wait() */
		if (waitqueue_active(&area->wq))
			wake_up(&area->wq);

		tsk->utask->xol_vaddr = 0;
	}
}