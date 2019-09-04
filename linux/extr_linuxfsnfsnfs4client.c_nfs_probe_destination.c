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
struct nfs_server {TYPE_1__* super; } ;
struct nfs_fattr {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_root; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 struct nfs_fattr* nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (struct nfs_fattr*) ; 
 int nfs_probe_fsinfo (struct nfs_server*,int /*<<< orphan*/ ,struct nfs_fattr*) ; 

__attribute__((used)) static int nfs_probe_destination(struct nfs_server *server)
{
	struct inode *inode = d_inode(server->super->s_root);
	struct nfs_fattr *fattr;
	int error;

	fattr = nfs_alloc_fattr();
	if (fattr == NULL)
		return -ENOMEM;

	/* Sanity: the probe won't work if the destination server
	 * does not recognize the migrated FH. */
	error = nfs_probe_fsinfo(server, NFS_FH(inode), fattr);

	nfs_free_fattr(fattr);
	return error;
}