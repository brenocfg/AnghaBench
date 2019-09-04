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
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int __nfs3_proc_setacls (struct inode*,struct posix_acl*,struct posix_acl*) ; 

int nfs3_proc_setacls(struct inode *inode, struct posix_acl *acl,
		struct posix_acl *dfacl)
{
	int ret;
	ret = __nfs3_proc_setacls(inode, acl, dfacl);
	return (ret == -EOPNOTSUPP) ? 0 : ret;

}