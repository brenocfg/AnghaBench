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
struct selinux_state {int dummy; } ;
struct selinux_fs_info {int policy_opened; int /*<<< orphan*/  mutex; struct selinux_state* state; } ;
struct policy_load_memory {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct inode {TYPE_1__* i_sb; } ;
struct file {struct policy_load_memory* private_data; } ;
struct TYPE_2__ {struct selinux_fs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct policy_load_memory*) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SECCLASS_SECURITY ; 
 int /*<<< orphan*/  SECINITSID_SECURITY ; 
 int /*<<< orphan*/  SECURITY__READ_POLICY ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct policy_load_memory*) ; 
 struct policy_load_memory* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ security_policydb_len (struct selinux_state*) ; 
 int security_read_policy (struct selinux_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sel_open_policy(struct inode *inode, struct file *filp)
{
	struct selinux_fs_info *fsi = inode->i_sb->s_fs_info;
	struct selinux_state *state = fsi->state;
	struct policy_load_memory *plm = NULL;
	int rc;

	BUG_ON(filp->private_data);

	mutex_lock(&fsi->mutex);

	rc = avc_has_perm(&selinux_state,
			  current_sid(), SECINITSID_SECURITY,
			  SECCLASS_SECURITY, SECURITY__READ_POLICY, NULL);
	if (rc)
		goto err;

	rc = -EBUSY;
	if (fsi->policy_opened)
		goto err;

	rc = -ENOMEM;
	plm = kzalloc(sizeof(*plm), GFP_KERNEL);
	if (!plm)
		goto err;

	if (i_size_read(inode) != security_policydb_len(state)) {
		inode_lock(inode);
		i_size_write(inode, security_policydb_len(state));
		inode_unlock(inode);
	}

	rc = security_read_policy(state, &plm->data, &plm->len);
	if (rc)
		goto err;

	fsi->policy_opened = 1;

	filp->private_data = plm;

	mutex_unlock(&fsi->mutex);

	return 0;
err:
	mutex_unlock(&fsi->mutex);

	if (plm)
		vfree(plm->data);
	kfree(plm);
	return rc;
}