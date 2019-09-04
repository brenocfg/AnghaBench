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
struct ext4_renament {int dir_nlink_delta; int /*<<< orphan*/  dir; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_dec_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_inc_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext4_update_dir_count(handle_t *handle, struct ext4_renament *ent)
{
	if (ent->dir_nlink_delta) {
		if (ent->dir_nlink_delta == -1)
			ext4_dec_count(handle, ent->dir);
		else
			ext4_inc_count(handle, ent->dir);
		ext4_mark_inode_dirty(handle, ent->dir);
	}
}