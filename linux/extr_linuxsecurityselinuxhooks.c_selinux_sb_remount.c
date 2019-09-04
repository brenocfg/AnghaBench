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
struct security_mnt_opts {char** mnt_opts; int* mnt_opts_flags; int num_mnt_opts; } ;
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct TYPE_2__ {int fs_flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  CONTEXT_MNT 131 
#define  DEFCONTEXT_MNT 130 
 int EINVAL ; 
 int ENOMEM ; 
#define  FSCONTEXT_MNT 129 
 int FS_BINARY_MOUNTDATA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  ROOTCONTEXT_MNT 128 
 int SBLABEL_MNT ; 
 int SE_SBINITIALIZED ; 
 char* alloc_secdata () ; 
 struct inode_security_struct* backing_inode_security (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bad_option (struct superblock_security_struct*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_secdata (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,int /*<<< orphan*/ ,...) ; 
 int security_context_str_to_sid (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_free_mnt_opts (struct security_mnt_opts*) ; 
 int /*<<< orphan*/  security_init_mnt_opts (struct security_mnt_opts*) ; 
 int selinux_parse_opts_str (char*,struct security_mnt_opts*) ; 
 int selinux_sb_copy_data (void*,char*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_sb_remount(struct super_block *sb, void *data)
{
	int rc, i, *flags;
	struct security_mnt_opts opts;
	char *secdata, **mount_options;
	struct superblock_security_struct *sbsec = sb->s_security;

	if (!(sbsec->flags & SE_SBINITIALIZED))
		return 0;

	if (!data)
		return 0;

	if (sb->s_type->fs_flags & FS_BINARY_MOUNTDATA)
		return 0;

	security_init_mnt_opts(&opts);
	secdata = alloc_secdata();
	if (!secdata)
		return -ENOMEM;
	rc = selinux_sb_copy_data(data, secdata);
	if (rc)
		goto out_free_secdata;

	rc = selinux_parse_opts_str(secdata, &opts);
	if (rc)
		goto out_free_secdata;

	mount_options = opts.mnt_opts;
	flags = opts.mnt_opts_flags;

	for (i = 0; i < opts.num_mnt_opts; i++) {
		u32 sid;

		if (flags[i] == SBLABEL_MNT)
			continue;
		rc = security_context_str_to_sid(&selinux_state,
						 mount_options[i], &sid,
						 GFP_KERNEL);
		if (rc) {
			pr_warn("SELinux: security_context_str_to_sid"
			       "(%s) failed for (dev %s, type %s) errno=%d\n",
			       mount_options[i], sb->s_id, sb->s_type->name, rc);
			goto out_free_opts;
		}
		rc = -EINVAL;
		switch (flags[i]) {
		case FSCONTEXT_MNT:
			if (bad_option(sbsec, FSCONTEXT_MNT, sbsec->sid, sid))
				goto out_bad_option;
			break;
		case CONTEXT_MNT:
			if (bad_option(sbsec, CONTEXT_MNT, sbsec->mntpoint_sid, sid))
				goto out_bad_option;
			break;
		case ROOTCONTEXT_MNT: {
			struct inode_security_struct *root_isec;
			root_isec = backing_inode_security(sb->s_root);

			if (bad_option(sbsec, ROOTCONTEXT_MNT, root_isec->sid, sid))
				goto out_bad_option;
			break;
		}
		case DEFCONTEXT_MNT:
			if (bad_option(sbsec, DEFCONTEXT_MNT, sbsec->def_sid, sid))
				goto out_bad_option;
			break;
		default:
			goto out_free_opts;
		}
	}

	rc = 0;
out_free_opts:
	security_free_mnt_opts(&opts);
out_free_secdata:
	free_secdata(secdata);
	return rc;
out_bad_option:
	pr_warn("SELinux: unable to change security options "
	       "during remount (dev %s, type=%s)\n", sb->s_id,
	       sb->s_type->name);
	goto out_free_opts;
}