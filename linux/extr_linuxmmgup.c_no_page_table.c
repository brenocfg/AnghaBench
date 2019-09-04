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
struct vm_area_struct {TYPE_1__* vm_ops; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int FOLL_DUMP ; 

__attribute__((used)) static struct page *no_page_table(struct vm_area_struct *vma,
		unsigned int flags)
{
	/*
	 * When core dumping an enormous anonymous area that nobody
	 * has touched so far, we don't want to allocate unnecessary pages or
	 * page tables.  Return error instead of NULL to skip handle_mm_fault,
	 * then get_dump_page() will return NULL to leave a hole in the dump.
	 * But we can only make this optimization where a hole would surely
	 * be zero-filled if handle_mm_fault() actually did handle it.
	 */
	if ((flags & FOLL_DUMP) && (!vma->vm_ops || !vma->vm_ops->fault))
		return ERR_PTR(-EFAULT);
	return NULL;
}