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
struct nfs_server {TYPE_1__* nfs_client; } ;
struct nfs4_minor_version_ops {int (* test_and_free_expired ) (struct nfs_server*,int /*<<< orphan*/ *,struct cred const*) ;} ;
struct inode {int dummy; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
struct TYPE_2__ {struct nfs4_minor_version_ops* cl_mvops; } ;

/* Variables and functions */
 int NFS4ERR_BAD_STATEID ; 
 int NFS4ERR_EXPIRED ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs_remove_bad_delegation (struct inode*,int /*<<< orphan*/ *) ; 
 int stub1 (struct nfs_server*,int /*<<< orphan*/ *,struct cred const*) ; 

__attribute__((used)) static void
nfs_delegation_test_free_expired(struct inode *inode,
		nfs4_stateid *stateid,
		const struct cred *cred)
{
	struct nfs_server *server = NFS_SERVER(inode);
	const struct nfs4_minor_version_ops *ops = server->nfs_client->cl_mvops;
	int status;

	if (!cred)
		return;
	status = ops->test_and_free_expired(server, stateid, cred);
	if (status == -NFS4ERR_EXPIRED || status == -NFS4ERR_BAD_STATEID)
		nfs_remove_bad_delegation(inode, stateid);
}