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
struct inode {int dummy; } ;
struct f2fs_dentry_ptr {int /*<<< orphan*/  filename; int /*<<< orphan*/  dentry; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  nr_bitmap; int /*<<< orphan*/  max; struct inode* inode; } ;
struct f2fs_dentry_block {int /*<<< orphan*/  filename; int /*<<< orphan*/  dentry; int /*<<< orphan*/  dentry_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_DENTRY_IN_BLOCK ; 
 int /*<<< orphan*/  SIZE_OF_DENTRY_BITMAP ; 

__attribute__((used)) static inline void make_dentry_ptr_block(struct inode *inode,
		struct f2fs_dentry_ptr *d, struct f2fs_dentry_block *t)
{
	d->inode = inode;
	d->max = NR_DENTRY_IN_BLOCK;
	d->nr_bitmap = SIZE_OF_DENTRY_BITMAP;
	d->bitmap = t->dentry_bitmap;
	d->dentry = t->dentry;
	d->filename = t->filename;
}