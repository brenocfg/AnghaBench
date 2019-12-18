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
struct user_namespace {int dummy; } ;
struct task_struct {int dummy; } ;
struct mm_struct {int flags; int def_flags; int /*<<< orphan*/  user_ns; int /*<<< orphan*/ * pmd_huge_pte; int /*<<< orphan*/  exe_file; int /*<<< orphan*/  arg_lock; int /*<<< orphan*/  page_table_lock; int /*<<< orphan*/  rss_stat; int /*<<< orphan*/  pinned_vm; scalar_t__ locked_vm; scalar_t__ map_count; int /*<<< orphan*/ * core_state; int /*<<< orphan*/  mmlist; int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/  mm_count; int /*<<< orphan*/  mm_users; scalar_t__ vmacache_seqnum; int /*<<< orphan*/  mm_rb; int /*<<< orphan*/ * mmap; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int flags; int def_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MMF_INIT_MASK ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int VM_INIT_DEF_MASK ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* current ; 
 int default_dump_filter ; 
 int /*<<< orphan*/  free_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  get_user_ns (struct user_namespace*) ; 
 scalar_t__ init_new_context (struct task_struct*,struct mm_struct*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_tlb_flush_pending (struct mm_struct*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mm_alloc_pgd (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_free_pgd (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_init_aio (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_init_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_init_owner (struct mm_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  mm_init_uprobes_state (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_pgtables_bytes_init (struct mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_mm_init (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mm_struct *mm_init(struct mm_struct *mm, struct task_struct *p,
	struct user_namespace *user_ns)
{
	mm->mmap = NULL;
	mm->mm_rb = RB_ROOT;
	mm->vmacache_seqnum = 0;
	atomic_set(&mm->mm_users, 1);
	atomic_set(&mm->mm_count, 1);
	init_rwsem(&mm->mmap_sem);
	INIT_LIST_HEAD(&mm->mmlist);
	mm->core_state = NULL;
	mm_pgtables_bytes_init(mm);
	mm->map_count = 0;
	mm->locked_vm = 0;
	atomic64_set(&mm->pinned_vm, 0);
	memset(&mm->rss_stat, 0, sizeof(mm->rss_stat));
	spin_lock_init(&mm->page_table_lock);
	spin_lock_init(&mm->arg_lock);
	mm_init_cpumask(mm);
	mm_init_aio(mm);
	mm_init_owner(mm, p);
	RCU_INIT_POINTER(mm->exe_file, NULL);
	mmu_notifier_mm_init(mm);
	init_tlb_flush_pending(mm);
#if defined(CONFIG_TRANSPARENT_HUGEPAGE) && !USE_SPLIT_PMD_PTLOCKS
	mm->pmd_huge_pte = NULL;
#endif
	mm_init_uprobes_state(mm);

	if (current->mm) {
		mm->flags = current->mm->flags & MMF_INIT_MASK;
		mm->def_flags = current->mm->def_flags & VM_INIT_DEF_MASK;
	} else {
		mm->flags = default_dump_filter;
		mm->def_flags = 0;
	}

	if (mm_alloc_pgd(mm))
		goto fail_nopgd;

	if (init_new_context(p, mm))
		goto fail_nocontext;

	mm->user_ns = get_user_ns(user_ns);
	return mm;

fail_nocontext:
	mm_free_pgd(mm);
fail_nopgd:
	free_mm(mm);
	return NULL;
}