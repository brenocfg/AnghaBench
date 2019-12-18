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
struct vm_area_struct {int dummy; } ;
struct to_kill {scalar_t__ size_shift; int /*<<< orphan*/  nd; struct task_struct* tsk; int /*<<< orphan*/  addr; } ;
struct task_struct {int /*<<< orphan*/  comm; } ;
struct page {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  compound_head (struct page*) ; 
 scalar_t__ compound_order (int /*<<< orphan*/ ) ; 
 scalar_t__ dev_pagemap_mapping_shift (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 scalar_t__ is_zone_device_page (struct page*) ; 
 int /*<<< orphan*/  kfree (struct to_kill*) ; 
 struct to_kill* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  page_address_in_vma (struct page*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_to_kill(struct task_struct *tsk, struct page *p,
		       struct vm_area_struct *vma,
		       struct list_head *to_kill,
		       struct to_kill **tkc)
{
	struct to_kill *tk;

	if (*tkc) {
		tk = *tkc;
		*tkc = NULL;
	} else {
		tk = kmalloc(sizeof(struct to_kill), GFP_ATOMIC);
		if (!tk) {
			pr_err("Memory failure: Out of memory while machine check handling\n");
			return;
		}
	}
	tk->addr = page_address_in_vma(p, vma);
	if (is_zone_device_page(p))
		tk->size_shift = dev_pagemap_mapping_shift(p, vma);
	else
		tk->size_shift = compound_order(compound_head(p)) + PAGE_SHIFT;

	/*
	 * Send SIGKILL if "tk->addr == -EFAULT". Also, as
	 * "tk->size_shift" is always non-zero for !is_zone_device_page(),
	 * so "tk->size_shift == 0" effectively checks no mapping on
	 * ZONE_DEVICE. Indeed, when a devdax page is mmapped N times
	 * to a process' address space, it's possible not all N VMAs
	 * contain mappings for the page, but at least one VMA does.
	 * Only deliver SIGBUS with payload derived from the VMA that
	 * has a mapping for the page.
	 */
	if (tk->addr == -EFAULT) {
		pr_info("Memory failure: Unable to find user space address %lx in %s\n",
			page_to_pfn(p), tsk->comm);
	} else if (tk->size_shift == 0) {
		kfree(tk);
		return;
	}
	get_task_struct(tsk);
	tk->tsk = tsk;
	list_add_tail(&tk->nd, to_kill);
}