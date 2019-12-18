#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qstr {int dummy; } ;
struct nfs4_secinfo_flavors {int dummy; } ;
struct nfs4_exception {int interruptible; scalar_t__ retry; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nfs_client; } ;

/* Variables and functions */
 int NFS4ERR_WRONGSEC ; 
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 scalar_t__ _nfs4_is_integrity_protected (int /*<<< orphan*/ ) ; 
 int _nfs4_proc_secinfo (struct inode*,struct qstr const*,struct nfs4_secinfo_flavors*,int) ; 
 int nfs4_handle_exception (TYPE_1__*,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  trace_nfs4_secinfo (struct inode*,struct qstr const*,int) ; 

int nfs4_proc_secinfo(struct inode *dir, const struct qstr *name,
		      struct nfs4_secinfo_flavors *flavors)
{
	struct nfs4_exception exception = {
		.interruptible = true,
	};
	int err;
	do {
		err = -NFS4ERR_WRONGSEC;

		/* try to use integrity protection with machine cred */
		if (_nfs4_is_integrity_protected(NFS_SERVER(dir)->nfs_client))
			err = _nfs4_proc_secinfo(dir, name, flavors, true);

		/*
		 * if unable to use integrity protection, or SECINFO with
		 * integrity protection returns NFS4ERR_WRONGSEC (which is
		 * disallowed by spec, but exists in deployed servers) use
		 * the current filesystem's rpc_client and the user cred.
		 */
		if (err == -NFS4ERR_WRONGSEC)
			err = _nfs4_proc_secinfo(dir, name, flavors, false);

		trace_nfs4_secinfo(dir, name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	} while (exception.retry);
	return err;
}