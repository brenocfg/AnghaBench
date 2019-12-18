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
struct ext4_renament {int /*<<< orphan*/  dir_bh; TYPE_1__* dir; TYPE_2__* parent_de; int /*<<< orphan*/  dir_inlined; int /*<<< orphan*/  inode; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  inode; } ;
struct TYPE_3__ {scalar_t__ i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (int /*<<< orphan*/ ,char*) ; 
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  ext4_get_first_dir_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_rename_dir_prepare(handle_t *handle, struct ext4_renament *ent)
{
	int retval;

	ent->dir_bh = ext4_get_first_dir_block(handle, ent->inode,
					      &retval, &ent->parent_de,
					      &ent->dir_inlined);
	if (!ent->dir_bh)
		return retval;
	if (le32_to_cpu(ent->parent_de->inode) != ent->dir->i_ino)
		return -EFSCORRUPTED;
	BUFFER_TRACE(ent->dir_bh, "get_write_access");
	return ext4_journal_get_write_access(handle, ent->dir_bh);
}