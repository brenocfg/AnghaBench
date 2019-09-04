#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dotsOK; } ;
struct msdos_sb_info {TYPE_2__ options; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fat_slot_info {int /*<<< orphan*/  bh; TYPE_1__* de; } ;
struct TYPE_3__ {int attr; } ;

/* Variables and functions */
 int ATTR_HIDDEN ; 
 int ENOENT ; 
 int MSDOS_NAME ; 
 struct msdos_sb_info* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int fat_scan (struct inode*,unsigned char*,struct fat_slot_info*) ; 
 int msdos_format_name (unsigned char const*,int,unsigned char*,TYPE_2__*) ; 

__attribute__((used)) static int msdos_find(struct inode *dir, const unsigned char *name, int len,
		      struct fat_slot_info *sinfo)
{
	struct msdos_sb_info *sbi = MSDOS_SB(dir->i_sb);
	unsigned char msdos_name[MSDOS_NAME];
	int err;

	err = msdos_format_name(name, len, msdos_name, &sbi->options);
	if (err)
		return -ENOENT;

	err = fat_scan(dir, msdos_name, sinfo);
	if (!err && sbi->options.dotsOK) {
		if (name[0] == '.') {
			if (!(sinfo->de->attr & ATTR_HIDDEN))
				err = -ENOENT;
		} else {
			if (sinfo->de->attr & ATTR_HIDDEN)
				err = -ENOENT;
		}
		if (err)
			brelse(sinfo->bh);
	}
	return err;
}