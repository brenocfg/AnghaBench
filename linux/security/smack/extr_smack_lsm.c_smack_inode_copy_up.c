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
struct task_smack {struct smack_known* smk_task; } ;
struct smack_known {int dummy; } ;
struct inode_smack {struct smack_known* smk_inode; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 struct cred* prepare_creds () ; 
 struct task_smack* smack_cred (struct cred*) ; 
 struct inode_smack* smack_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smack_inode_copy_up(struct dentry *dentry, struct cred **new)
{

	struct task_smack *tsp;
	struct smack_known *skp;
	struct inode_smack *isp;
	struct cred *new_creds = *new;

	if (new_creds == NULL) {
		new_creds = prepare_creds();
		if (new_creds == NULL)
			return -ENOMEM;
	}

	tsp = smack_cred(new_creds);

	/*
	 * Get label from overlay inode and set it in create_sid
	 */
	isp = smack_inode(d_inode(dentry->d_parent));
	skp = isp->smk_inode;
	tsp->smk_task = skp;
	*new = new_creds;
	return 0;
}