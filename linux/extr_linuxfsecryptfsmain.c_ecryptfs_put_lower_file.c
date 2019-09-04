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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct ecryptfs_inode_info {int /*<<< orphan*/  lower_file_mutex; int /*<<< orphan*/ * lower_file; int /*<<< orphan*/  lower_file_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ecryptfs_inode_info* ecryptfs_inode_to_private (struct inode*) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ecryptfs_put_lower_file(struct inode *inode)
{
	struct ecryptfs_inode_info *inode_info;

	inode_info = ecryptfs_inode_to_private(inode);
	if (atomic_dec_and_mutex_lock(&inode_info->lower_file_count,
				      &inode_info->lower_file_mutex)) {
		filemap_write_and_wait(inode->i_mapping);
		fput(inode_info->lower_file);
		inode_info->lower_file = NULL;
		mutex_unlock(&inode_info->lower_file_mutex);
	}
}