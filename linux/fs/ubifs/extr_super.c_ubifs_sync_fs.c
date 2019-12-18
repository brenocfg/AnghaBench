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
struct TYPE_4__ {int /*<<< orphan*/  ubi_num; } ;
struct ubifs_info {int jhead_cnt; TYPE_2__ vi; TYPE_1__* jheads; } ;
struct super_block {struct ubifs_info* s_fs_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  wbuf; } ;

/* Variables and functions */
 int ubi_sync (int /*<<< orphan*/ ) ; 
 int ubifs_run_commit (struct ubifs_info*) ; 
 int ubifs_wbuf_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ubifs_sync_fs(struct super_block *sb, int wait)
{
	int i, err;
	struct ubifs_info *c = sb->s_fs_info;

	/*
	 * Zero @wait is just an advisory thing to help the file system shove
	 * lots of data into the queues, and there will be the second
	 * '->sync_fs()' call, with non-zero @wait.
	 */
	if (!wait)
		return 0;

	/*
	 * Synchronize write buffers, because 'ubifs_run_commit()' does not
	 * do this if it waits for an already running commit.
	 */
	for (i = 0; i < c->jhead_cnt; i++) {
		err = ubifs_wbuf_sync(&c->jheads[i].wbuf);
		if (err)
			return err;
	}

	/*
	 * Strictly speaking, it is not necessary to commit the journal here,
	 * synchronizing write-buffers would be enough. But committing makes
	 * UBIFS free space predictions much more accurate, so we want to let
	 * the user be able to get more accurate results of 'statfs()' after
	 * they synchronize the file system.
	 */
	err = ubifs_run_commit(c);
	if (err)
		return err;

	return ubi_sync(c->vi.ubi_num);
}