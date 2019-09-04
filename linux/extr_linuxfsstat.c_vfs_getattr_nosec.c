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
typedef  int /*<<< orphan*/  u32 ;
struct path {int /*<<< orphan*/  dentry; } ;
struct kstat {int /*<<< orphan*/  result_mask; } ;
struct inode {TYPE_1__* i_op; } ;
struct TYPE_2__ {int (* getattr ) (struct path const*,struct kstat*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 unsigned int KSTAT_QUERY_FLAGS ; 
 int /*<<< orphan*/  STATX_ALL ; 
 int /*<<< orphan*/  STATX_BASIC_STATS ; 
 struct inode* d_backing_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int /*<<< orphan*/  memset (struct kstat*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct path const*,struct kstat*,int /*<<< orphan*/ ,unsigned int) ; 

int vfs_getattr_nosec(const struct path *path, struct kstat *stat,
		      u32 request_mask, unsigned int query_flags)
{
	struct inode *inode = d_backing_inode(path->dentry);

	memset(stat, 0, sizeof(*stat));
	stat->result_mask |= STATX_BASIC_STATS;
	request_mask &= STATX_ALL;
	query_flags &= KSTAT_QUERY_FLAGS;
	if (inode->i_op->getattr)
		return inode->i_op->getattr(path, stat, request_mask,
					    query_flags);

	generic_fillattr(inode, stat);
	return 0;
}