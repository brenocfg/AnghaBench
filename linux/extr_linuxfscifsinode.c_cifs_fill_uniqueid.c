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
struct cifs_sb_info {int mnt_cifs_flags; } ;
struct cifs_fattr {int /*<<< orphan*/  cf_uniqueid; } ;

/* Variables and functions */
 int CIFS_MOUNT_SERVER_INUM ; 
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  ROOT_I ; 
 int /*<<< orphan*/  iunique (struct super_block*,int /*<<< orphan*/ ) ; 

void
cifs_fill_uniqueid(struct super_block *sb, struct cifs_fattr *fattr)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(sb);

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM)
		return;

	fattr->cf_uniqueid = iunique(sb, ROOT_I);
}