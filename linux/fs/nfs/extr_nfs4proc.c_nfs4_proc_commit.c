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
struct nfs_server {int dummy; } ;
struct nfs_commitres {int dummy; } ;
struct nfs_commitargs {int /*<<< orphan*/  count; int /*<<< orphan*/  offset; } ;
struct nfs4_exception {scalar_t__ retry; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int _nfs4_proc_commit (struct file*,struct nfs_commitargs*,struct nfs_commitres*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int nfs4_handle_exception (struct nfs_server*,int,struct nfs4_exception*) ; 

int nfs4_proc_commit(struct file *dst, __u64 offset, __u32 count, struct nfs_commitres *res)
{
	struct nfs_commitargs args = {
		.offset = offset,
		.count = count,
	};
	struct nfs_server *dst_server = NFS_SERVER(file_inode(dst));
	struct nfs4_exception exception = { };
	int status;

	do {
		status = _nfs4_proc_commit(dst, &args, res);
		status = nfs4_handle_exception(dst_server, status, &exception);
	} while (exception.retry);

	return status;
}