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
struct inode {int /*<<< orphan*/  i_lock; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int cache_validity; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int NFS_INO_DATA_INVAL_DEFER ; 
 int NFS_INO_INVALID_DATA ; 
 int NFS_INO_INVALID_SIZE ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int inode_newsize_ok (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 

__attribute__((used)) static int nfs_vmtruncate(struct inode * inode, loff_t offset)
{
	int err;

	err = inode_newsize_ok(inode, offset);
	if (err)
		goto out;

	i_size_write(inode, offset);
	/* Optimisation */
	if (offset == 0)
		NFS_I(inode)->cache_validity &= ~(NFS_INO_INVALID_DATA |
				NFS_INO_DATA_INVAL_DEFER);
	NFS_I(inode)->cache_validity &= ~NFS_INO_INVALID_SIZE;

	spin_unlock(&inode->i_lock);
	truncate_pagecache(inode, offset);
	spin_lock(&inode->i_lock);
out:
	return err;
}