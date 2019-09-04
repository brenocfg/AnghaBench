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
typedef  int u32 ;
struct inode_security_struct {int /*<<< orphan*/  sclass; int /*<<< orphan*/  sid; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int DIR__ADD_NAME ; 
 int DIR__REMOVE_NAME ; 
 int DIR__REPARENT ; 
 int DIR__RMDIR ; 
 int DIR__SEARCH ; 
 int FILE__RENAME ; 
 int FILE__UNLINK ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_DENTRY ; 
 int /*<<< orphan*/  SECCLASS_DIR ; 
 int avc_has_perm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct common_audit_data*) ; 
 struct inode_security_struct* backing_inode_security (struct dentry*) ; 
 int current_sid () ; 
 int d_is_dir (struct dentry*) ; 
 scalar_t__ d_is_positive (struct dentry*) ; 
 struct inode_security_struct* inode_security (struct inode*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static inline int may_rename(struct inode *old_dir,
			     struct dentry *old_dentry,
			     struct inode *new_dir,
			     struct dentry *new_dentry)
{
	struct inode_security_struct *old_dsec, *new_dsec, *old_isec, *new_isec;
	struct common_audit_data ad;
	u32 sid = current_sid();
	u32 av;
	int old_is_dir, new_is_dir;
	int rc;

	old_dsec = inode_security(old_dir);
	old_isec = backing_inode_security(old_dentry);
	old_is_dir = d_is_dir(old_dentry);
	new_dsec = inode_security(new_dir);

	ad.type = LSM_AUDIT_DATA_DENTRY;

	ad.u.dentry = old_dentry;
	rc = avc_has_perm(&selinux_state,
			  sid, old_dsec->sid, SECCLASS_DIR,
			  DIR__REMOVE_NAME | DIR__SEARCH, &ad);
	if (rc)
		return rc;
	rc = avc_has_perm(&selinux_state,
			  sid, old_isec->sid,
			  old_isec->sclass, FILE__RENAME, &ad);
	if (rc)
		return rc;
	if (old_is_dir && new_dir != old_dir) {
		rc = avc_has_perm(&selinux_state,
				  sid, old_isec->sid,
				  old_isec->sclass, DIR__REPARENT, &ad);
		if (rc)
			return rc;
	}

	ad.u.dentry = new_dentry;
	av = DIR__ADD_NAME | DIR__SEARCH;
	if (d_is_positive(new_dentry))
		av |= DIR__REMOVE_NAME;
	rc = avc_has_perm(&selinux_state,
			  sid, new_dsec->sid, SECCLASS_DIR, av, &ad);
	if (rc)
		return rc;
	if (d_is_positive(new_dentry)) {
		new_isec = backing_inode_security(new_dentry);
		new_is_dir = d_is_dir(new_dentry);
		rc = avc_has_perm(&selinux_state,
				  sid, new_isec->sid,
				  new_isec->sclass,
				  (new_is_dir ? DIR__RMDIR : FILE__UNLINK), &ad);
		if (rc)
			return rc;
	}

	return 0;
}