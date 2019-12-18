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
struct timespec64 {int dummy; } ;
struct msdos_sb_info {int dummy; } ;
struct msdos_dir_entry {scalar_t__ size; void* date; void* time; scalar_t__ ctime_cs; scalar_t__ ctime; scalar_t__ adate; scalar_t__ cdate; scalar_t__ lcase; int /*<<< orphan*/  attr; int /*<<< orphan*/  name; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fat_slot_info {int dummy; } ;
typedef  void* __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ARCH ; 
 int /*<<< orphan*/  ATTR_DIR ; 
 int /*<<< orphan*/  ATTR_HIDDEN ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 int /*<<< orphan*/  MSDOS_NAME ; 
 struct msdos_sb_info* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int S_CTIME ; 
 int S_MTIME ; 
 int fat_add_entries (struct inode*,struct msdos_dir_entry*,int,struct fat_slot_info*) ; 
 int /*<<< orphan*/  fat_set_start (struct msdos_dir_entry*,int) ; 
 int /*<<< orphan*/  fat_sync_inode (struct inode*) ; 
 int /*<<< orphan*/  fat_time_unix2fat (struct msdos_sb_info*,struct timespec64*,void**,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fat_truncate_time (struct inode*,struct timespec64*,int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msdos_add_entry(struct inode *dir, const unsigned char *name,
			   int is_dir, int is_hid, int cluster,
			   struct timespec64 *ts, struct fat_slot_info *sinfo)
{
	struct msdos_sb_info *sbi = MSDOS_SB(dir->i_sb);
	struct msdos_dir_entry de;
	__le16 time, date;
	int err;

	memcpy(de.name, name, MSDOS_NAME);
	de.attr = is_dir ? ATTR_DIR : ATTR_ARCH;
	if (is_hid)
		de.attr |= ATTR_HIDDEN;
	de.lcase = 0;
	fat_time_unix2fat(sbi, ts, &time, &date, NULL);
	de.cdate = de.adate = 0;
	de.ctime = 0;
	de.ctime_cs = 0;
	de.time = time;
	de.date = date;
	fat_set_start(&de, cluster);
	de.size = 0;

	err = fat_add_entries(dir, &de, 1, sinfo);
	if (err)
		return err;

	fat_truncate_time(dir, ts, S_CTIME|S_MTIME);
	if (IS_DIRSYNC(dir))
		(void)fat_sync_inode(dir);
	else
		mark_inode_dirty(dir);

	return 0;
}