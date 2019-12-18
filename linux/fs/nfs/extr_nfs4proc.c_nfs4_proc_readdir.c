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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct nfs4_exception {int interruptible; scalar_t__ retry; } ;
struct dentry {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_SERVER (int /*<<< orphan*/ ) ; 
 int _nfs4_proc_readdir (struct dentry*,struct cred const*,int /*<<< orphan*/ ,struct page**,unsigned int,int) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int nfs4_handle_exception (int /*<<< orphan*/ ,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  trace_nfs4_readdir (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nfs4_proc_readdir(struct dentry *dentry, const struct cred *cred,
		u64 cookie, struct page **pages, unsigned int count, bool plus)
{
	struct nfs4_exception exception = {
		.interruptible = true,
	};
	int err;
	do {
		err = _nfs4_proc_readdir(dentry, cred, cookie,
				pages, count, plus);
		trace_nfs4_readdir(d_inode(dentry), err);
		err = nfs4_handle_exception(NFS_SERVER(d_inode(dentry)), err,
				&exception);
	} while (exception.retry);
	return err;
}