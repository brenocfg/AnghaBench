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
struct super_block {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  prepath; } ;
struct cifs_mnt_data {struct cifs_sb_info* cifs_sb; } ;

/* Variables and functions */
 int CIFS_MOUNT_USE_PREFIX_PATH ; 
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
match_prepath(struct super_block *sb, struct cifs_mnt_data *mnt_data)
{
	struct cifs_sb_info *old = CIFS_SB(sb);
	struct cifs_sb_info *new = mnt_data->cifs_sb;
	bool old_set = old->mnt_cifs_flags & CIFS_MOUNT_USE_PREFIX_PATH;
	bool new_set = new->mnt_cifs_flags & CIFS_MOUNT_USE_PREFIX_PATH;

	if (old_set && new_set && !strcmp(new->prepath, old->prepath))
		return 1;
	else if (!old_set && !new_set)
		return 1;

	return 0;
}