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
struct xfs_mount {struct super_block* m_super; } ;
struct super_block {int /*<<< orphan*/  s_umount; } ;

/* Variables and functions */
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_inodes_sb (struct super_block*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void
xfs_flush_inodes(
	struct xfs_mount	*mp)
{
	struct super_block	*sb = mp->m_super;

	if (down_read_trylock(&sb->s_umount)) {
		sync_inodes_sb(sb);
		up_read(&sb->s_umount);
	}
}