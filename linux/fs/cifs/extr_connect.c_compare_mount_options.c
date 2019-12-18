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
struct super_block {int s_flags; } ;
struct cifs_sb_info {unsigned int mnt_cifs_flags; scalar_t__ wsize; scalar_t__ rsize; scalar_t__ mnt_file_mode; scalar_t__ mnt_dir_mode; scalar_t__ actimeo; TYPE_1__* local_nls; int /*<<< orphan*/  mnt_gid; int /*<<< orphan*/  mnt_uid; scalar_t__ mnt_cifs_serverino_autodisabled; } ;
struct cifs_mnt_data {int flags; struct cifs_sb_info* cifs_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  charset; } ;

/* Variables and functions */
 unsigned int CIFS_MOUNT_MASK ; 
 unsigned int CIFS_MOUNT_SERVER_INUM ; 
 int CIFS_MS_MASK ; 
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_mount_options(struct super_block *sb, struct cifs_mnt_data *mnt_data)
{
	struct cifs_sb_info *old = CIFS_SB(sb);
	struct cifs_sb_info *new = mnt_data->cifs_sb;
	unsigned int oldflags = old->mnt_cifs_flags & CIFS_MOUNT_MASK;
	unsigned int newflags = new->mnt_cifs_flags & CIFS_MOUNT_MASK;

	if ((sb->s_flags & CIFS_MS_MASK) != (mnt_data->flags & CIFS_MS_MASK))
		return 0;

	if (old->mnt_cifs_serverino_autodisabled)
		newflags &= ~CIFS_MOUNT_SERVER_INUM;

	if (oldflags != newflags)
		return 0;

	/*
	 * We want to share sb only if we don't specify an r/wsize or
	 * specified r/wsize is greater than or equal to existing one.
	 */
	if (new->wsize && new->wsize < old->wsize)
		return 0;

	if (new->rsize && new->rsize < old->rsize)
		return 0;

	if (!uid_eq(old->mnt_uid, new->mnt_uid) || !gid_eq(old->mnt_gid, new->mnt_gid))
		return 0;

	if (old->mnt_file_mode != new->mnt_file_mode ||
	    old->mnt_dir_mode != new->mnt_dir_mode)
		return 0;

	if (strcmp(old->local_nls->charset, new->local_nls->charset))
		return 0;

	if (old->actimeo != new->actimeo)
		return 0;

	return 1;
}