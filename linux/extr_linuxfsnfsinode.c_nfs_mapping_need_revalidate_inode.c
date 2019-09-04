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

/* Variables and functions */
 int /*<<< orphan*/  NFS_INO_REVAL_PAGECACHE ; 
 scalar_t__ NFS_STALE (struct inode*) ; 
 scalar_t__ nfs_check_cache_invalid (struct inode*,int /*<<< orphan*/ ) ; 

bool nfs_mapping_need_revalidate_inode(struct inode *inode)
{
	return nfs_check_cache_invalid(inode, NFS_INO_REVAL_PAGECACHE) ||
		NFS_STALE(inode);
}