#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  cache_validity; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSIOS_EXTENDWRITE ; 
 TYPE_2__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_INVALID_SIZE ; 
 int PAGE_SHIFT ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 
 int page_file_offset (struct page*) ; 
 int page_index (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_grow_file(struct page *page, unsigned int offset, unsigned int count)
{
	struct inode *inode = page_file_mapping(page)->host;
	loff_t end, i_size;
	pgoff_t end_index;

	spin_lock(&inode->i_lock);
	i_size = i_size_read(inode);
	end_index = (i_size - 1) >> PAGE_SHIFT;
	if (i_size > 0 && page_index(page) < end_index)
		goto out;
	end = page_file_offset(page) + ((loff_t)offset+count);
	if (i_size >= end)
		goto out;
	i_size_write(inode, end);
	NFS_I(inode)->cache_validity &= ~NFS_INO_INVALID_SIZE;
	nfs_inc_stats(inode, NFSIOS_EXTENDWRITE);
out:
	spin_unlock(&inode->i_lock);
}