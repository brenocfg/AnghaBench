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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_STATUS ; 
 int /*<<< orphan*/  IMA_FS_BUSY ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ima_check_policy () ; 
 int /*<<< orphan*/  ima_delete_rules () ; 
 int /*<<< orphan*/  ima_fs_flags ; 
 int /*<<< orphan*/ * ima_policy ; 
 int /*<<< orphan*/  ima_update_policy () ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 int /*<<< orphan*/  securityfs_remove (int /*<<< orphan*/ *) ; 
 int seq_release (struct inode*,struct file*) ; 
 int valid_policy ; 

__attribute__((used)) static int ima_release_policy(struct inode *inode, struct file *file)
{
	const char *cause = valid_policy ? "completed" : "failed";

	if ((file->f_flags & O_ACCMODE) == O_RDONLY)
		return seq_release(inode, file);

	if (valid_policy && ima_check_policy() < 0) {
		cause = "failed";
		valid_policy = 0;
	}

	pr_info("policy update %s\n", cause);
	integrity_audit_msg(AUDIT_INTEGRITY_STATUS, NULL, NULL,
			    "policy_update", cause, !valid_policy, 0);

	if (!valid_policy) {
		ima_delete_rules();
		valid_policy = 1;
		clear_bit(IMA_FS_BUSY, &ima_fs_flags);
		return 0;
	}

	ima_update_policy();
#if !defined(CONFIG_IMA_WRITE_POLICY) && !defined(CONFIG_IMA_READ_POLICY)
	securityfs_remove(ima_policy);
	ima_policy = NULL;
#elif defined(CONFIG_IMA_WRITE_POLICY)
	clear_bit(IMA_FS_BUSY, &ima_fs_flags);
#elif defined(CONFIG_IMA_READ_POLICY)
	inode->i_mode &= ~S_IWUSR;
#endif
	return 0;
}