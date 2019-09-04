#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int u32 ;
struct vm_area_struct {int vm_pgoff; void* vm_start; } ;
struct TYPE_7__ {int flags; } ;
struct stack_map_irq_work {TYPE_2__ irq_work; TYPE_1__* sem; } ;
struct bpf_stack_build_id {void* status; void* offset; int /*<<< orphan*/  build_id; void* ip; } ;
struct TYPE_9__ {TYPE_3__* mm; } ;
struct TYPE_6__ {int /*<<< orphan*/  dep_map; } ;
struct TYPE_8__ {TYPE_1__ mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_BUILD_ID_SIZE ; 
 void* BPF_STACK_BUILD_ID_IP ; 
 void* BPF_STACK_BUILD_ID_VALID ; 
 int IRQ_WORK_BUSY ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 TYPE_5__* current ; 
 scalar_t__ down_read_trylock (TYPE_1__*) ; 
 struct vm_area_struct* find_vma (TYPE_3__*,void*) ; 
 scalar_t__ in_nmi () ; 
 int /*<<< orphan*/  irq_work_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwsem_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stack_map_get_build_id (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 struct stack_map_irq_work* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (TYPE_1__*) ; 
 int /*<<< orphan*/  up_read_work ; 

__attribute__((used)) static void stack_map_get_build_id_offset(struct bpf_stack_build_id *id_offs,
					  u64 *ips, u32 trace_nr, bool user)
{
	int i;
	struct vm_area_struct *vma;
	bool irq_work_busy = false;
	struct stack_map_irq_work *work = NULL;

	if (in_nmi()) {
		work = this_cpu_ptr(&up_read_work);
		if (work->irq_work.flags & IRQ_WORK_BUSY)
			/* cannot queue more up_read, fallback */
			irq_work_busy = true;
	}

	/*
	 * We cannot do up_read() in nmi context. To do build_id lookup
	 * in nmi context, we need to run up_read() in irq_work. We use
	 * a percpu variable to do the irq_work. If the irq_work is
	 * already used by another lookup, we fall back to report ips.
	 *
	 * Same fallback is used for kernel stack (!user) on a stackmap
	 * with build_id.
	 */
	if (!user || !current || !current->mm || irq_work_busy ||
	    down_read_trylock(&current->mm->mmap_sem) == 0) {
		/* cannot access current->mm, fall back to ips */
		for (i = 0; i < trace_nr; i++) {
			id_offs[i].status = BPF_STACK_BUILD_ID_IP;
			id_offs[i].ip = ips[i];
			memset(id_offs[i].build_id, 0, BPF_BUILD_ID_SIZE);
		}
		return;
	}

	for (i = 0; i < trace_nr; i++) {
		vma = find_vma(current->mm, ips[i]);
		if (!vma || stack_map_get_build_id(vma, id_offs[i].build_id)) {
			/* per entry fall back to ips */
			id_offs[i].status = BPF_STACK_BUILD_ID_IP;
			id_offs[i].ip = ips[i];
			memset(id_offs[i].build_id, 0, BPF_BUILD_ID_SIZE);
			continue;
		}
		id_offs[i].offset = (vma->vm_pgoff << PAGE_SHIFT) + ips[i]
			- vma->vm_start;
		id_offs[i].status = BPF_STACK_BUILD_ID_VALID;
	}

	if (!work) {
		up_read(&current->mm->mmap_sem);
	} else {
		work->sem = &current->mm->mmap_sem;
		irq_work_queue(&work->irq_work);
		/*
		 * The irq_work will release the mmap_sem with
		 * up_read_non_owner(). The rwsem_release() is called
		 * here to release the lock from lockdep's perspective.
		 */
		rwsem_release(&current->mm->mmap_sem.dep_map, 1, _RET_IP_);
	}
}