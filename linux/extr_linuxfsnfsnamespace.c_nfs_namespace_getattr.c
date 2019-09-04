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
struct kstat {int dummy; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 TYPE_1__* NFS_FH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (int /*<<< orphan*/ ,struct kstat*) ; 
 int nfs_getattr (struct path const*,struct kstat*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
nfs_namespace_getattr(const struct path *path, struct kstat *stat,
			u32 request_mask, unsigned int query_flags)
{
	if (NFS_FH(d_inode(path->dentry))->size != 0)
		return nfs_getattr(path, stat, request_mask, query_flags);
	generic_fillattr(d_inode(path->dentry), stat);
	return 0;
}