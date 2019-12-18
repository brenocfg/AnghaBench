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
struct rpc_clnt {int dummy; } ;
struct qstr {int dummy; } ;
struct page {int dummy; } ;
struct nfs4_fs_locations {int dummy; } ;
struct nfs4_exception {int interruptible; scalar_t__ retry; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int _nfs4_proc_fs_locations (struct rpc_clnt*,struct inode*,struct qstr const*,struct nfs4_fs_locations*,struct page*) ; 
 int nfs4_handle_exception (int /*<<< orphan*/ ,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  trace_nfs4_get_fs_locations (struct inode*,struct qstr const*,int) ; 

int nfs4_proc_fs_locations(struct rpc_clnt *client, struct inode *dir,
			   const struct qstr *name,
			   struct nfs4_fs_locations *fs_locations,
			   struct page *page)
{
	struct nfs4_exception exception = {
		.interruptible = true,
	};
	int err;
	do {
		err = _nfs4_proc_fs_locations(client, dir, name,
				fs_locations, page);
		trace_nfs4_get_fs_locations(dir, name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	} while (exception.retry);
	return err;
}