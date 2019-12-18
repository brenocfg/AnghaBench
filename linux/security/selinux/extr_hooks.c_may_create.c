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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct task_security_struct {int /*<<< orphan*/  sid; } ;
struct superblock_security_struct {int /*<<< orphan*/  sid; } ;
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct inode {TYPE_1__* i_sb; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct common_audit_data {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {struct superblock_security_struct* s_security; } ;

/* Variables and functions */
 int DIR__ADD_NAME ; 
 int DIR__SEARCH ; 
 int FILESYSTEM__ASSOCIATE ; 
 int FILE__CREATE ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_DENTRY ; 
 int /*<<< orphan*/  SECCLASS_DIR ; 
 int /*<<< orphan*/  SECCLASS_FILESYSTEM ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct common_audit_data*) ; 
 int /*<<< orphan*/  current_cred () ; 
 struct inode_security_struct* inode_security (struct inode*) ; 
 struct task_security_struct* selinux_cred (int /*<<< orphan*/ ) ; 
 int selinux_determine_inode_label (struct task_security_struct*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int may_create(struct inode *dir,
		      struct dentry *dentry,
		      u16 tclass)
{
	const struct task_security_struct *tsec = selinux_cred(current_cred());
	struct inode_security_struct *dsec;
	struct superblock_security_struct *sbsec;
	u32 sid, newsid;
	struct common_audit_data ad;
	int rc;

	dsec = inode_security(dir);
	sbsec = dir->i_sb->s_security;

	sid = tsec->sid;

	ad.type = LSM_AUDIT_DATA_DENTRY;
	ad.u.dentry = dentry;

	rc = avc_has_perm(&selinux_state,
			  sid, dsec->sid, SECCLASS_DIR,
			  DIR__ADD_NAME | DIR__SEARCH,
			  &ad);
	if (rc)
		return rc;

	rc = selinux_determine_inode_label(selinux_cred(current_cred()), dir,
					   &dentry->d_name, tclass, &newsid);
	if (rc)
		return rc;

	rc = avc_has_perm(&selinux_state,
			  sid, newsid, tclass, FILE__CREATE, &ad);
	if (rc)
		return rc;

	return avc_has_perm(&selinux_state,
			    newsid, sbsec->sid,
			    SECCLASS_FILESYSTEM,
			    FILESYSTEM__ASSOCIATE, &ad);
}