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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_pgoff; unsigned long vm_end; struct file* vm_file; } ;
struct file {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 long EBADF ; 
 scalar_t__ IS_DAX (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  force_page_cache_readahead (int /*<<< orphan*/ ,struct file*,unsigned long,unsigned long) ; 

__attribute__((used)) static long madvise_willneed(struct vm_area_struct *vma,
			     struct vm_area_struct **prev,
			     unsigned long start, unsigned long end)
{
	struct file *file = vma->vm_file;

	*prev = vma;
#ifdef CONFIG_SWAP
	if (!file) {
		force_swapin_readahead(vma, start, end);
		return 0;
	}

	if (shmem_mapping(file->f_mapping)) {
		force_shm_swapin_readahead(vma, start, end,
					file->f_mapping);
		return 0;
	}
#else
	if (!file)
		return -EBADF;
#endif

	if (IS_DAX(file_inode(file))) {
		/* no bad return value, but ignore advice */
		return 0;
	}

	start = ((start - vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff;
	if (end > vma->vm_end)
		end = vma->vm_end;
	end = ((end - vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff;

	force_page_cache_readahead(file->f_mapping, file, start, end - start);
	return 0;
}