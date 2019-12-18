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
typedef  int /*<<< orphan*/  u32 ;
struct task_security_struct {int /*<<< orphan*/  create_sid; } ;
struct qstr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;
typedef  struct cred const cred ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_mode_to_security_class (int) ; 
 struct task_security_struct* selinux_cred (struct cred const*) ; 
 int selinux_determine_inode_label (struct task_security_struct*,int /*<<< orphan*/ ,struct qstr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int selinux_dentry_create_files_as(struct dentry *dentry, int mode,
					  struct qstr *name,
					  const struct cred *old,
					  struct cred *new)
{
	u32 newsid;
	int rc;
	struct task_security_struct *tsec;

	rc = selinux_determine_inode_label(selinux_cred(old),
					   d_inode(dentry->d_parent), name,
					   inode_mode_to_security_class(mode),
					   &newsid);
	if (rc)
		return rc;

	tsec = selinux_cred(new);
	tsec->create_sid = newsid;
	return 0;
}