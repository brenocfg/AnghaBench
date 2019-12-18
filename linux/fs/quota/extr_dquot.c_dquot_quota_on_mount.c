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
struct super_block {int /*<<< orphan*/  s_root; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int DQUOT_LIMITS_ENABLED ; 
 int DQUOT_USAGE_ENABLED ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* lookup_one_len_unlocked (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int security_quota_on (struct dentry*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int vfs_load_quota_inode (int /*<<< orphan*/ ,int,int,int) ; 

int dquot_quota_on_mount(struct super_block *sb, char *qf_name,
		int format_id, int type)
{
	struct dentry *dentry;
	int error;

	dentry = lookup_one_len_unlocked(qf_name, sb->s_root, strlen(qf_name));
	if (IS_ERR(dentry))
		return PTR_ERR(dentry);

	if (d_really_is_negative(dentry)) {
		error = -ENOENT;
		goto out;
	}

	error = security_quota_on(dentry);
	if (!error)
		error = vfs_load_quota_inode(d_inode(dentry), type, format_id,
				DQUOT_USAGE_ENABLED | DQUOT_LIMITS_ENABLED);

out:
	dput(dentry);
	return error;
}