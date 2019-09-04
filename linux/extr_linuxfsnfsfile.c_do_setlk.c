#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file_lock {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
struct TYPE_6__ {int (* lock ) (struct file*,int,struct file_lock*) ;int /*<<< orphan*/  (* have_delegation ) (struct inode*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_READ ; 
 TYPE_4__* NFS_PROTO (struct inode*) ; 
 int locks_lock_file_wait (struct file*,struct file_lock*) ; 
 scalar_t__ mapping_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_revalidate_mapping (struct inode*,TYPE_1__*) ; 
 int nfs_sync_mapping (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_zap_caches (struct inode*) ; 
 int stub1 (struct file*,int,struct file_lock*) ; 
 int /*<<< orphan*/  stub2 (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_setlk(struct file *filp, int cmd, struct file_lock *fl, int is_local)
{
	struct inode *inode = filp->f_mapping->host;
	int status;

	/*
	 * Flush all pending writes before doing anything
	 * with locks..
	 */
	status = nfs_sync_mapping(filp->f_mapping);
	if (status != 0)
		goto out;

	/*
	 * Use local locking if mounted with "-onolock" or with appropriate
	 * "-olocal_lock="
	 */
	if (!is_local)
		status = NFS_PROTO(inode)->lock(filp, cmd, fl);
	else
		status = locks_lock_file_wait(filp, fl);
	if (status < 0)
		goto out;

	/*
	 * Invalidate cache to prevent missing any changes.  If
	 * the file is mapped, clear the page cache as well so
	 * those mappings will be loaded.
	 *
	 * This makes locking act as a cache coherency point.
	 */
	nfs_sync_mapping(filp->f_mapping);
	if (!NFS_PROTO(inode)->have_delegation(inode, FMODE_READ)) {
		nfs_zap_caches(inode);
		if (mapping_mapped(filp->f_mapping))
			nfs_revalidate_mapping(inode, filp->f_mapping);
	}
out:
	return status;
}