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
typedef  scalar_t__ u64 ;
struct page {int dummy; } ;
struct TYPE_2__ {scalar_t__ pos; scalar_t__ version; scalar_t__ size; int /*<<< orphan*/  lock; scalar_t__ cached; } ;
struct fuse_inode {TYPE_1__ rdc; } ;
struct fuse_dirent {scalar_t__ off; } ;
struct file {int /*<<< orphan*/  f_mapping; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 size_t FUSE_DIRENT_SIZE (struct fuse_dirent*) ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clear_page (void*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 struct page* find_lock_page (int /*<<< orphan*/ ,scalar_t__) ; 
 struct page* find_or_create_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct fuse_inode* get_fuse_inode (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  mapping_gfp_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,struct fuse_dirent*,size_t) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void fuse_add_dirent_to_cache(struct file *file,
				     struct fuse_dirent *dirent, loff_t pos)
{
	struct fuse_inode *fi = get_fuse_inode(file_inode(file));
	size_t reclen = FUSE_DIRENT_SIZE(dirent);
	pgoff_t index;
	struct page *page;
	loff_t size;
	u64 version;
	unsigned int offset;
	void *addr;

	spin_lock(&fi->rdc.lock);
	/*
	 * Is cache already completed?  Or this entry does not go at the end of
	 * cache?
	 */
	if (fi->rdc.cached || pos != fi->rdc.pos) {
		spin_unlock(&fi->rdc.lock);
		return;
	}
	version = fi->rdc.version;
	size = fi->rdc.size;
	offset = size & ~PAGE_MASK;
	index = size >> PAGE_SHIFT;
	/* Dirent doesn't fit in current page?  Jump to next page. */
	if (offset + reclen > PAGE_SIZE) {
		index++;
		offset = 0;
	}
	spin_unlock(&fi->rdc.lock);

	if (offset) {
		page = find_lock_page(file->f_mapping, index);
	} else {
		page = find_or_create_page(file->f_mapping, index,
					   mapping_gfp_mask(file->f_mapping));
	}
	if (!page)
		return;

	spin_lock(&fi->rdc.lock);
	/* Raced with another readdir */
	if (fi->rdc.version != version || fi->rdc.size != size ||
	    WARN_ON(fi->rdc.pos != pos))
		goto unlock;

	addr = kmap_atomic(page);
	if (!offset)
		clear_page(addr);
	memcpy(addr + offset, dirent, reclen);
	kunmap_atomic(addr);
	fi->rdc.size = (index << PAGE_SHIFT) + offset + reclen;
	fi->rdc.pos = dirent->off;
unlock:
	spin_unlock(&fi->rdc.lock);
	unlock_page(page);
	put_page(page);
}