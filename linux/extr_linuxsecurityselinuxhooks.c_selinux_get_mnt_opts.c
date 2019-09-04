#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct superblock_security_struct {int flags; TYPE_1__* sb; int /*<<< orphan*/  def_sid; int /*<<< orphan*/  mntpoint_sid; int /*<<< orphan*/  sid; } ;
struct super_block {struct superblock_security_struct* s_security; } ;
struct security_mnt_opts {int num_mnt_opts; char** mnt_opts; int* mnt_opts_flags; } ;
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct dentry {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  initialized; } ;
struct TYPE_4__ {struct dentry* s_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int CONTEXT_MNT ; 
 int DEFCONTEXT_MNT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FSCONTEXT_MNT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NUM_SEL_MNT_OPTS ; 
 int ROOTCONTEXT_MNT ; 
 int SBLABEL_MNT ; 
 int SE_MNTMASK ; 
 int SE_SBINITIALIZED ; 
 struct inode_security_struct* backing_inode_security (struct dentry*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_free_mnt_opts (struct security_mnt_opts*) ; 
 int /*<<< orphan*/  security_init_mnt_opts (struct security_mnt_opts*) ; 
 int security_sid_to_context (TYPE_2__*,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 TYPE_2__ selinux_state ; 

__attribute__((used)) static int selinux_get_mnt_opts(const struct super_block *sb,
				struct security_mnt_opts *opts)
{
	int rc = 0, i;
	struct superblock_security_struct *sbsec = sb->s_security;
	char *context = NULL;
	u32 len;
	char tmp;

	security_init_mnt_opts(opts);

	if (!(sbsec->flags & SE_SBINITIALIZED))
		return -EINVAL;

	if (!selinux_state.initialized)
		return -EINVAL;

	/* make sure we always check enough bits to cover the mask */
	BUILD_BUG_ON(SE_MNTMASK >= (1 << NUM_SEL_MNT_OPTS));

	tmp = sbsec->flags & SE_MNTMASK;
	/* count the number of mount options for this sb */
	for (i = 0; i < NUM_SEL_MNT_OPTS; i++) {
		if (tmp & 0x01)
			opts->num_mnt_opts++;
		tmp >>= 1;
	}
	/* Check if the Label support flag is set */
	if (sbsec->flags & SBLABEL_MNT)
		opts->num_mnt_opts++;

	opts->mnt_opts = kcalloc(opts->num_mnt_opts, sizeof(char *), GFP_ATOMIC);
	if (!opts->mnt_opts) {
		rc = -ENOMEM;
		goto out_free;
	}

	opts->mnt_opts_flags = kcalloc(opts->num_mnt_opts, sizeof(int), GFP_ATOMIC);
	if (!opts->mnt_opts_flags) {
		rc = -ENOMEM;
		goto out_free;
	}

	i = 0;
	if (sbsec->flags & FSCONTEXT_MNT) {
		rc = security_sid_to_context(&selinux_state, sbsec->sid,
					     &context, &len);
		if (rc)
			goto out_free;
		opts->mnt_opts[i] = context;
		opts->mnt_opts_flags[i++] = FSCONTEXT_MNT;
	}
	if (sbsec->flags & CONTEXT_MNT) {
		rc = security_sid_to_context(&selinux_state,
					     sbsec->mntpoint_sid,
					     &context, &len);
		if (rc)
			goto out_free;
		opts->mnt_opts[i] = context;
		opts->mnt_opts_flags[i++] = CONTEXT_MNT;
	}
	if (sbsec->flags & DEFCONTEXT_MNT) {
		rc = security_sid_to_context(&selinux_state, sbsec->def_sid,
					     &context, &len);
		if (rc)
			goto out_free;
		opts->mnt_opts[i] = context;
		opts->mnt_opts_flags[i++] = DEFCONTEXT_MNT;
	}
	if (sbsec->flags & ROOTCONTEXT_MNT) {
		struct dentry *root = sbsec->sb->s_root;
		struct inode_security_struct *isec = backing_inode_security(root);

		rc = security_sid_to_context(&selinux_state, isec->sid,
					     &context, &len);
		if (rc)
			goto out_free;
		opts->mnt_opts[i] = context;
		opts->mnt_opts_flags[i++] = ROOTCONTEXT_MNT;
	}
	if (sbsec->flags & SBLABEL_MNT) {
		opts->mnt_opts[i] = NULL;
		opts->mnt_opts_flags[i++] = SBLABEL_MNT;
	}

	BUG_ON(i != opts->num_mnt_opts);

	return 0;

out_free:
	security_free_mnt_opts(opts);
	return rc;
}