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
struct the_nilfs {struct nilfs_sc_info* ns_writer; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_sc_info {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 scalar_t__ NILFS_MDT_INODE (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_doing_construction () ; 
 int /*<<< orphan*/  nilfs_segctor_do_flush (struct nilfs_sc_info*,int /*<<< orphan*/ ) ; 

void nilfs_flush_segment(struct super_block *sb, ino_t ino)
{
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct nilfs_sc_info *sci = nilfs->ns_writer;

	if (!sci || nilfs_doing_construction())
		return;
	nilfs_segctor_do_flush(sci, NILFS_MDT_INODE(sb, ino) ? ino : 0);
					/* assign bit 0 to data files */
}