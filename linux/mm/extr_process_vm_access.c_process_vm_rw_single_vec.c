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
struct task_struct {int dummy; } ;
struct pages {int dummy; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct iov_iter {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EFAULT ; 
 unsigned int FOLL_WRITE ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 int PVM_MAX_KMALLOC_PAGES ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int get_user_pages_remote (struct task_struct*,struct mm_struct*,unsigned long,int,unsigned int,struct page**,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 int min (unsigned long,unsigned long) ; 
 int process_vm_rw_pages (struct page**,unsigned long,size_t,struct iov_iter*,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_vm_rw_single_vec(unsigned long addr,
				    unsigned long len,
				    struct iov_iter *iter,
				    struct page **process_pages,
				    struct mm_struct *mm,
				    struct task_struct *task,
				    int vm_write)
{
	unsigned long pa = addr & PAGE_MASK;
	unsigned long start_offset = addr - pa;
	unsigned long nr_pages;
	ssize_t rc = 0;
	unsigned long max_pages_per_loop = PVM_MAX_KMALLOC_PAGES
		/ sizeof(struct pages *);
	unsigned int flags = 0;

	/* Work out address and page range required */
	if (len == 0)
		return 0;
	nr_pages = (addr + len - 1) / PAGE_SIZE - addr / PAGE_SIZE + 1;

	if (vm_write)
		flags |= FOLL_WRITE;

	while (!rc && nr_pages && iov_iter_count(iter)) {
		int pages = min(nr_pages, max_pages_per_loop);
		int locked = 1;
		size_t bytes;

		/*
		 * Get the pages we're interested in.  We must
		 * access remotely because task/mm might not
		 * current/current->mm
		 */
		down_read(&mm->mmap_sem);
		pages = get_user_pages_remote(task, mm, pa, pages, flags,
					      process_pages, NULL, &locked);
		if (locked)
			up_read(&mm->mmap_sem);
		if (pages <= 0)
			return -EFAULT;

		bytes = pages * PAGE_SIZE - start_offset;
		if (bytes > len)
			bytes = len;

		rc = process_vm_rw_pages(process_pages,
					 start_offset, bytes, iter,
					 vm_write);
		len -= bytes;
		start_offset = 0;
		nr_pages -= pages;
		pa += pages * PAGE_SIZE;
		while (pages)
			put_page(process_pages[--pages]);
	}

	return rc;
}