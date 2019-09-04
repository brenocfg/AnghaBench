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
struct super_block {scalar_t__ s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  ffs_data_closed (scalar_t__) ; 
 int /*<<< orphan*/  ffs_release_dev (scalar_t__) ; 
 int /*<<< orphan*/  kill_litter_super (struct super_block*) ; 

__attribute__((used)) static void
ffs_fs_kill_sb(struct super_block *sb)
{
	ENTER();

	kill_litter_super(sb);
	if (sb->s_fs_info) {
		ffs_release_dev(sb->s_fs_info);
		ffs_data_closed(sb->s_fs_info);
	}
}