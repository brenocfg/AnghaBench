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
struct task_smack {TYPE_1__* smk_task; } ;
struct qstr {int dummy; } ;
struct inode_smack {int smk_flags; TYPE_1__* smk_inode; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;
typedef  struct cred const cred ;
struct TYPE_2__ {int /*<<< orphan*/  smk_rules; int /*<<< orphan*/  smk_known; } ;

/* Variables and functions */
 int MAY_TRANSMUTE ; 
 int SMK_INODE_TRANSMUTE ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct task_smack* smack_cred (struct cred const*) ; 
 struct inode_smack* smack_inode (int /*<<< orphan*/ ) ; 
 int smk_access_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smack_dentry_create_files_as(struct dentry *dentry, int mode,
					struct qstr *name,
					const struct cred *old,
					struct cred *new)
{
	struct task_smack *otsp = smack_cred(old);
	struct task_smack *ntsp = smack_cred(new);
	struct inode_smack *isp;
	int may;

	/*
	 * Use the process credential unless all of
	 * the transmuting criteria are met
	 */
	ntsp->smk_task = otsp->smk_task;

	/*
	 * the attribute of the containing directory
	 */
	isp = smack_inode(d_inode(dentry->d_parent));

	if (isp->smk_flags & SMK_INODE_TRANSMUTE) {
		rcu_read_lock();
		may = smk_access_entry(otsp->smk_task->smk_known,
				       isp->smk_inode->smk_known,
				       &otsp->smk_task->smk_rules);
		rcu_read_unlock();

		/*
		 * If the directory is transmuting and the rule
		 * providing access is transmuting use the containing
		 * directory label instead of the process label.
		 */
		if (may > 0 && (may & MAY_TRANSMUTE))
			ntsp->smk_task = isp->smk_inode;
	}
	return 0;
}