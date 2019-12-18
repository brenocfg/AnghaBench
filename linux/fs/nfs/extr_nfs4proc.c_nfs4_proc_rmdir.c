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
struct qstr {int dummy; } ;
struct nfs4_exception {int interruptible; scalar_t__ retry; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF4DIR ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int _nfs4_proc_remove (struct inode*,struct qstr const*,int /*<<< orphan*/ ) ; 
 int nfs4_handle_exception (int /*<<< orphan*/ ,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  trace_nfs4_remove (struct inode*,struct qstr const*,int) ; 

__attribute__((used)) static int nfs4_proc_rmdir(struct inode *dir, const struct qstr *name)
{
	struct nfs4_exception exception = {
		.interruptible = true,
	};
	int err;

	do {
		err = _nfs4_proc_remove(dir, name, NF4DIR);
		trace_nfs4_remove(dir, name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	} while (exception.retry);
	return err;
}