#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dentry {TYPE_2__* d_sb; } ;
struct cred {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dentry; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILESYSTEM__GETATTR ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_DENTRY ; 
 struct cred* current_cred () ; 
 int superblock_has_perm (struct cred const*,TYPE_2__*,int /*<<< orphan*/ ,struct common_audit_data*) ; 

__attribute__((used)) static int selinux_sb_statfs(struct dentry *dentry)
{
	const struct cred *cred = current_cred();
	struct common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_DENTRY;
	ad.u.dentry = dentry->d_sb->s_root;
	return superblock_has_perm(cred, dentry->d_sb, FILESYSTEM__GETATTR, &ad);
}