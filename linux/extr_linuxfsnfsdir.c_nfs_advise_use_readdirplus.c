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
struct nfs_inode {int /*<<< orphan*/  flags; int /*<<< orphan*/  open_files; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CAP_READDIRPLUS ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_ADVISE_RDPLUS ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_server_capable (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfs_advise_use_readdirplus(struct inode *dir)
{
	struct nfs_inode *nfsi = NFS_I(dir);

	if (nfs_server_capable(dir, NFS_CAP_READDIRPLUS) &&
	    !list_empty(&nfsi->open_files))
		set_bit(NFS_INO_ADVISE_RDPLUS, &nfsi->flags);
}