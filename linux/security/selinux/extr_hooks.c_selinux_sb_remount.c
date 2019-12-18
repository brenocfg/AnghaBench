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
typedef  int /*<<< orphan*/  u32 ;
struct superblock_security_struct {int flags; int /*<<< orphan*/  def_sid; int /*<<< orphan*/  mntpoint_sid; int /*<<< orphan*/  sid; } ;
struct super_block {TYPE_1__* s_type; int /*<<< orphan*/  s_id; int /*<<< orphan*/  s_root; struct superblock_security_struct* s_security; } ;
struct selinux_mnt_opts {scalar_t__ defcontext; scalar_t__ rootcontext; scalar_t__ context; scalar_t__ fscontext; } ;
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_MNT ; 
 int /*<<< orphan*/  DEFCONTEXT_MNT ; 
 int EINVAL ; 
 int /*<<< orphan*/  FSCONTEXT_MNT ; 
 int /*<<< orphan*/  ROOTCONTEXT_MNT ; 
 int SE_SBINITIALIZED ; 
 struct inode_security_struct* backing_inode_security (int /*<<< orphan*/ ) ; 
 scalar_t__ bad_option (struct superblock_security_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_sid (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_sb_remount(struct super_block *sb, void *mnt_opts)
{
	struct selinux_mnt_opts *opts = mnt_opts;
	struct superblock_security_struct *sbsec = sb->s_security;
	u32 sid;
	int rc;

	if (!(sbsec->flags & SE_SBINITIALIZED))
		return 0;

	if (!opts)
		return 0;

	if (opts->fscontext) {
		rc = parse_sid(sb, opts->fscontext, &sid);
		if (rc)
			return rc;
		if (bad_option(sbsec, FSCONTEXT_MNT, sbsec->sid, sid))
			goto out_bad_option;
	}
	if (opts->context) {
		rc = parse_sid(sb, opts->context, &sid);
		if (rc)
			return rc;
		if (bad_option(sbsec, CONTEXT_MNT, sbsec->mntpoint_sid, sid))
			goto out_bad_option;
	}
	if (opts->rootcontext) {
		struct inode_security_struct *root_isec;
		root_isec = backing_inode_security(sb->s_root);
		rc = parse_sid(sb, opts->rootcontext, &sid);
		if (rc)
			return rc;
		if (bad_option(sbsec, ROOTCONTEXT_MNT, root_isec->sid, sid))
			goto out_bad_option;
	}
	if (opts->defcontext) {
		rc = parse_sid(sb, opts->defcontext, &sid);
		if (rc)
			return rc;
		if (bad_option(sbsec, DEFCONTEXT_MNT, sbsec->def_sid, sid))
			goto out_bad_option;
	}
	return 0;

out_bad_option:
	pr_warn("SELinux: unable to change security options "
	       "during remount (dev %s, type=%s)\n", sb->s_id,
	       sb->s_type->name);
	return -EINVAL;
}