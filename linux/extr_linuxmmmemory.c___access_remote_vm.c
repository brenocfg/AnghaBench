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
struct task_struct {int dummy; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 unsigned int FOLL_WRITE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  copy_from_user_page (struct vm_area_struct*,struct page*,unsigned long,void*,void*,int) ; 
 int /*<<< orphan*/  copy_to_user_page (struct vm_area_struct*,struct page*,unsigned long,void*,void*,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int get_user_pages_remote (struct task_struct*,struct mm_struct*,unsigned long,int,unsigned int,struct page**,struct vm_area_struct**,int /*<<< orphan*/ *) ; 
 void* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int __access_remote_vm(struct task_struct *tsk, struct mm_struct *mm,
		unsigned long addr, void *buf, int len, unsigned int gup_flags)
{
	struct vm_area_struct *vma;
	void *old_buf = buf;
	int write = gup_flags & FOLL_WRITE;

	down_read(&mm->mmap_sem);
	/* ignore errors, just check how much was successfully transferred */
	while (len) {
		int bytes, ret, offset;
		void *maddr;
		struct page *page = NULL;

		ret = get_user_pages_remote(tsk, mm, addr, 1,
				gup_flags, &page, &vma, NULL);
		if (ret <= 0) {
#ifndef CONFIG_HAVE_IOREMAP_PROT
			break;
#else
			/*
			 * Check if this is a VM_IO | VM_PFNMAP VMA, which
			 * we can access using slightly different code.
			 */
			vma = find_vma(mm, addr);
			if (!vma || vma->vm_start > addr)
				break;
			if (vma->vm_ops && vma->vm_ops->access)
				ret = vma->vm_ops->access(vma, addr, buf,
							  len, write);
			if (ret <= 0)
				break;
			bytes = ret;
#endif
		} else {
			bytes = len;
			offset = addr & (PAGE_SIZE-1);
			if (bytes > PAGE_SIZE-offset)
				bytes = PAGE_SIZE-offset;

			maddr = kmap(page);
			if (write) {
				copy_to_user_page(vma, page, addr,
						  maddr + offset, buf, bytes);
				set_page_dirty_lock(page);
			} else {
				copy_from_user_page(vma, page, addr,
						    buf, maddr + offset, bytes);
			}
			kunmap(page);
			put_page(page);
		}
		len -= bytes;
		buf += bytes;
		addr += bytes;
	}
	up_read(&mm->mmap_sem);

	return buf - old_buf;
}