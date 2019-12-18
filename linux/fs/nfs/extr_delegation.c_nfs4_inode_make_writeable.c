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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nfs_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_WRITE ; 
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs4_check_delegation (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_has_session (int /*<<< orphan*/ ) ; 
 int nfs4_inode_return_delegation (struct inode*) ; 

int nfs4_inode_make_writeable(struct inode *inode)
{
	if (!nfs4_has_session(NFS_SERVER(inode)->nfs_client) ||
	    !nfs4_check_delegation(inode, FMODE_WRITE))
		return nfs4_inode_return_delegation(inode);
	return 0;
}