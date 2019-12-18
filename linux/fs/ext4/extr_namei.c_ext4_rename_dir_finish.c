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
struct ext4_renament {TYPE_1__* dir; int /*<<< orphan*/  inode; int /*<<< orphan*/  dir_bh; int /*<<< orphan*/  dir_inlined; TYPE_2__* parent_de; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int ext4_handle_dirty_dirblock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext4_handle_dirty_dx_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_dx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_rename_dir_finish(handle_t *handle, struct ext4_renament *ent,
				  unsigned dir_ino)
{
	int retval;

	ent->parent_de->inode = cpu_to_le32(dir_ino);
	BUFFER_TRACE(ent->dir_bh, "call ext4_handle_dirty_metadata");
	if (!ent->dir_inlined) {
		if (is_dx(ent->inode)) {
			retval = ext4_handle_dirty_dx_node(handle,
							   ent->inode,
							   ent->dir_bh);
		} else {
			retval = ext4_handle_dirty_dirblock(handle, ent->inode,
							    ent->dir_bh);
		}
	} else {
		retval = ext4_mark_inode_dirty(handle, ent->inode);
	}
	if (retval) {
		ext4_std_error(ent->dir->i_sb, retval);
		return retval;
	}
	return 0;
}