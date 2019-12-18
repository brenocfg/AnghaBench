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
struct TYPE_2__ {int /*<<< orphan*/ * count; } ;
struct mm_struct {int /*<<< orphan*/  pmd_huge_pte; TYPE_1__ rss_stat; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON_MSG (int,char*) ; 
 int NR_MM_COUNTERS ; 
 int /*<<< orphan*/  VM_BUG_ON_MM (int /*<<< orphan*/ ,struct mm_struct*) ; 
 long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_pgtables_bytes (struct mm_struct*) ; 
 int /*<<< orphan*/  pr_alert (char*,struct mm_struct*,...) ; 
 int /*<<< orphan*/ * resident_page_types ; 
 scalar_t__ unlikely (long) ; 

__attribute__((used)) static void check_mm(struct mm_struct *mm)
{
	int i;

	BUILD_BUG_ON_MSG(ARRAY_SIZE(resident_page_types) != NR_MM_COUNTERS,
			 "Please make sure 'struct resident_page_types[]' is updated as well");

	for (i = 0; i < NR_MM_COUNTERS; i++) {
		long x = atomic_long_read(&mm->rss_stat.count[i]);

		if (unlikely(x))
			pr_alert("BUG: Bad rss-counter state mm:%p type:%s val:%ld\n",
				 mm, resident_page_types[i], x);
	}

	if (mm_pgtables_bytes(mm))
		pr_alert("BUG: non-zero pgtables_bytes on freeing mm: %ld\n",
				mm_pgtables_bytes(mm));

#if defined(CONFIG_TRANSPARENT_HUGEPAGE) && !USE_SPLIT_PMD_PTLOCKS
	VM_BUG_ON_MM(mm->pmd_huge_pte, mm);
#endif
}