#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {struct buffer_head* s_sbh; } ;

/* Variables and functions */
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ buffer_write_io_error (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_write_io_error (struct buffer_head*) ; 
 int /*<<< orphan*/  ext2_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

__attribute__((used)) static void ext2_clear_super_error(struct super_block *sb)
{
	struct buffer_head *sbh = EXT2_SB(sb)->s_sbh;

	if (buffer_write_io_error(sbh)) {
		/*
		 * Oh, dear.  A previous attempt to write the
		 * superblock failed.  This could happen because the
		 * USB device was yanked out.  Or it could happen to
		 * be a transient write error and maybe the block will
		 * be remapped.  Nothing we can do but to retry the
		 * write and hope for the best.
		 */
		ext2_msg(sb, KERN_ERR,
		       "previous I/O error to superblock detected");
		clear_buffer_write_io_error(sbh);
		set_buffer_uptodate(sbh);
	}
}