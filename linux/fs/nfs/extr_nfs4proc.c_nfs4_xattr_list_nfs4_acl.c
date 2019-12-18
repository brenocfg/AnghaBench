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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int nfs4_server_supports_acls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nfs4_xattr_list_nfs4_acl(struct dentry *dentry)
{
	return nfs4_server_supports_acls(NFS_SERVER(d_inode(dentry)));
}