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
struct nfs4_exception {scalar_t__ retry; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int __nfs4_proc_set_acl (struct inode*,void const*,size_t) ; 
 int nfs4_handle_exception (int /*<<< orphan*/ ,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  trace_nfs4_set_acl (struct inode*,int) ; 

__attribute__((used)) static int nfs4_proc_set_acl(struct inode *inode, const void *buf, size_t buflen)
{
	struct nfs4_exception exception = { };
	int err;
	do {
		err = __nfs4_proc_set_acl(inode, buf, buflen);
		trace_nfs4_set_acl(inode, err);
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	} while (exception.retry);
	return err;
}