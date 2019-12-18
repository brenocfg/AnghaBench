#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ext4_renament {int /*<<< orphan*/ * bh; TYPE_2__* dir; int /*<<< orphan*/  inlined; TYPE_1__* de; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; } ;
struct TYPE_6__ {unsigned int file_type; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  current_time (TYPE_2__*) ; 
 int ext4_handle_dirty_dirblock (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_has_feature_filetype (int /*<<< orphan*/ ) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inode_inc_iversion (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ext4_setent(handle_t *handle, struct ext4_renament *ent,
		       unsigned ino, unsigned file_type)
{
	int retval;

	BUFFER_TRACE(ent->bh, "get write access");
	retval = ext4_journal_get_write_access(handle, ent->bh);
	if (retval)
		return retval;
	ent->de->inode = cpu_to_le32(ino);
	if (ext4_has_feature_filetype(ent->dir->i_sb))
		ent->de->file_type = file_type;
	inode_inc_iversion(ent->dir);
	ent->dir->i_ctime = ent->dir->i_mtime =
		current_time(ent->dir);
	ext4_mark_inode_dirty(handle, ent->dir);
	BUFFER_TRACE(ent->bh, "call ext4_handle_dirty_metadata");
	if (!ent->inlined) {
		retval = ext4_handle_dirty_dirblock(handle, ent->dir, ent->bh);
		if (unlikely(retval)) {
			ext4_std_error(ent->dir->i_sb, retval);
			return retval;
		}
	}
	brelse(ent->bh);
	ent->bh = NULL;

	return 0;
}