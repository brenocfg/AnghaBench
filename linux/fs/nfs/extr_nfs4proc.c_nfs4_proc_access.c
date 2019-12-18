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
struct nfs_access_entry {int dummy; } ;
struct nfs4_exception {int interruptible; scalar_t__ retry; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int _nfs4_proc_access (struct inode*,struct nfs_access_entry*) ; 
 int nfs4_handle_exception (int /*<<< orphan*/ ,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  trace_nfs4_access (struct inode*,int) ; 

__attribute__((used)) static int nfs4_proc_access(struct inode *inode, struct nfs_access_entry *entry)
{
	struct nfs4_exception exception = {
		.interruptible = true,
	};
	int err;
	do {
		err = _nfs4_proc_access(inode, entry);
		trace_nfs4_access(inode, err);
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	} while (exception.retry);
	return err;
}