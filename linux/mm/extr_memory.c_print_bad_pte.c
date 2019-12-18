#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {TYPE_4__* vm_file; TYPE_1__* vm_ops; int /*<<< orphan*/  anon_vma; int /*<<< orphan*/  vm_flags; int /*<<< orphan*/  vm_mm; } ;
struct page {int dummy; } ;
struct address_space {TYPE_3__* a_ops; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;
struct TYPE_10__ {int /*<<< orphan*/  comm; } ;
struct TYPE_9__ {TYPE_2__* f_op; struct address_space* f_mapping; } ;
struct TYPE_8__ {int /*<<< orphan*/ * readpage; } ;
struct TYPE_7__ {int /*<<< orphan*/ * mmap; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fault; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 int /*<<< orphan*/  TAINT_BAD_PAGE ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  dump_page (struct page*,char*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int jiffies ; 
 int /*<<< orphan*/  linear_page_index (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pgd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_alert (char*,...) ; 
 scalar_t__ pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static void print_bad_pte(struct vm_area_struct *vma, unsigned long addr,
			  pte_t pte, struct page *page)
{
	pgd_t *pgd = pgd_offset(vma->vm_mm, addr);
	p4d_t *p4d = p4d_offset(pgd, addr);
	pud_t *pud = pud_offset(p4d, addr);
	pmd_t *pmd = pmd_offset(pud, addr);
	struct address_space *mapping;
	pgoff_t index;
	static unsigned long resume;
	static unsigned long nr_shown;
	static unsigned long nr_unshown;

	/*
	 * Allow a burst of 60 reports, then keep quiet for that minute;
	 * or allow a steady drip of one report per second.
	 */
	if (nr_shown == 60) {
		if (time_before(jiffies, resume)) {
			nr_unshown++;
			return;
		}
		if (nr_unshown) {
			pr_alert("BUG: Bad page map: %lu messages suppressed\n",
				 nr_unshown);
			nr_unshown = 0;
		}
		nr_shown = 0;
	}
	if (nr_shown++ == 0)
		resume = jiffies + 60 * HZ;

	mapping = vma->vm_file ? vma->vm_file->f_mapping : NULL;
	index = linear_page_index(vma, addr);

	pr_alert("BUG: Bad page map in process %s  pte:%08llx pmd:%08llx\n",
		 current->comm,
		 (long long)pte_val(pte), (long long)pmd_val(*pmd));
	if (page)
		dump_page(page, "bad pte");
	pr_alert("addr:%px vm_flags:%08lx anon_vma:%px mapping:%px index:%lx\n",
		 (void *)addr, vma->vm_flags, vma->anon_vma, mapping, index);
	pr_alert("file:%pD fault:%ps mmap:%ps readpage:%ps\n",
		 vma->vm_file,
		 vma->vm_ops ? vma->vm_ops->fault : NULL,
		 vma->vm_file ? vma->vm_file->f_op->mmap : NULL,
		 mapping ? mapping->a_ops->readpage : NULL);
	dump_stack();
	add_taint(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);
}