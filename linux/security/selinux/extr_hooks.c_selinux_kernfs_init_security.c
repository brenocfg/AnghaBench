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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct task_security_struct {int /*<<< orphan*/  sid; scalar_t__ create_sid; } ;
struct qstr {int /*<<< orphan*/  hash_len; int /*<<< orphan*/  name; } ;
struct kernfs_node {int /*<<< orphan*/  name; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XATTR_CREATE ; 
 int /*<<< orphan*/  XATTR_NAME_SELINUX ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  hashlen_string (struct kernfs_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_mode_to_security_class (int /*<<< orphan*/ ) ; 
 int kernfs_xattr_get (struct kernfs_node*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int kernfs_xattr_set (struct kernfs_node*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int security_context_to_sid (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int security_sid_to_context_force (int /*<<< orphan*/ *,scalar_t__,char**,scalar_t__*) ; 
 int security_transition_sid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct qstr*,scalar_t__*) ; 
 struct task_security_struct* selinux_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_kernfs_init_security(struct kernfs_node *kn_dir,
					struct kernfs_node *kn)
{
	const struct task_security_struct *tsec = selinux_cred(current_cred());
	u32 parent_sid, newsid, clen;
	int rc;
	char *context;

	rc = kernfs_xattr_get(kn_dir, XATTR_NAME_SELINUX, NULL, 0);
	if (rc == -ENODATA)
		return 0;
	else if (rc < 0)
		return rc;

	clen = (u32)rc;
	context = kmalloc(clen, GFP_KERNEL);
	if (!context)
		return -ENOMEM;

	rc = kernfs_xattr_get(kn_dir, XATTR_NAME_SELINUX, context, clen);
	if (rc < 0) {
		kfree(context);
		return rc;
	}

	rc = security_context_to_sid(&selinux_state, context, clen, &parent_sid,
				     GFP_KERNEL);
	kfree(context);
	if (rc)
		return rc;

	if (tsec->create_sid) {
		newsid = tsec->create_sid;
	} else {
		u16 secclass = inode_mode_to_security_class(kn->mode);
		struct qstr q;

		q.name = kn->name;
		q.hash_len = hashlen_string(kn_dir, kn->name);

		rc = security_transition_sid(&selinux_state, tsec->sid,
					     parent_sid, secclass, &q,
					     &newsid);
		if (rc)
			return rc;
	}

	rc = security_sid_to_context_force(&selinux_state, newsid,
					   &context, &clen);
	if (rc)
		return rc;

	rc = kernfs_xattr_set(kn, XATTR_NAME_SELINUX, context, clen,
			      XATTR_CREATE);
	kfree(context);
	return rc;
}