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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_AUDIT_DATA_DENTRY ; 
 int /*<<< orphan*/  __inode_security_revalidate (struct inode*,struct dentry*,int) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int inode_has_perm (struct cred const*,struct inode*,int /*<<< orphan*/ ,struct common_audit_data*) ; 

__attribute__((used)) static inline int dentry_has_perm(const struct cred *cred,
				  struct dentry *dentry,
				  u32 av)
{
	struct inode *inode = d_backing_inode(dentry);
	struct common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_DENTRY;
	ad.u.dentry = dentry;
	__inode_security_revalidate(inode, dentry, true);
	return inode_has_perm(cred, inode, av, &ad);
}