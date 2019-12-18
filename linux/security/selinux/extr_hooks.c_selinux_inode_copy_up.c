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
struct dentry {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct cred* prepare_creds () ; 
 struct task_security_struct* selinux_cred (struct cred*) ; 
 int /*<<< orphan*/  selinux_inode_getsecid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int selinux_inode_copy_up(struct dentry *src, struct cred **new)
{
	u32 sid;
	struct task_security_struct *tsec;
	struct cred *new_creds = *new;

	if (new_creds == NULL) {
		new_creds = prepare_creds();
		if (!new_creds)
			return -ENOMEM;
	}

	tsec = selinux_cred(new_creds);
	/* Get label from overlay inode and set it in create_sid */
	selinux_inode_getsecid(d_inode(src), &sid);
	tsec->create_sid = sid;
	*new = new_creds;
	return 0;
}