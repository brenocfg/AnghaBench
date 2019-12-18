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
struct TYPE_2__ {scalar_t__ pos; int cached; int /*<<< orphan*/  lock; int /*<<< orphan*/  size; } ;
struct fuse_inode {TYPE_1__ rdc; } ;
struct file {int /*<<< orphan*/  f_mapping; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 struct fuse_inode* get_fuse_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fuse_readdir_cache_end(struct file *file, loff_t pos)
{
	struct fuse_inode *fi = get_fuse_inode(file_inode(file));
	loff_t end;

	spin_lock(&fi->rdc.lock);
	/* does cache end position match current position? */
	if (fi->rdc.pos != pos) {
		spin_unlock(&fi->rdc.lock);
		return;
	}

	fi->rdc.cached = true;
	end = ALIGN(fi->rdc.size, PAGE_SIZE);
	spin_unlock(&fi->rdc.lock);

	/* truncate unused tail of cache */
	truncate_inode_pages(file->f_mapping, end);
}