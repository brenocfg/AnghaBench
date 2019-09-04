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
struct ubifs_info {int /*<<< orphan*/  commit_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_budg (char*,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ubifs_garbage_collect (struct ubifs_info*,int) ; 
 int ubifs_return_leb (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_gc(struct ubifs_info *c)
{
	int err, lnum;

	/* Make some free space by garbage-collecting dirty space */
	down_read(&c->commit_sem);
	lnum = ubifs_garbage_collect(c, 1);
	up_read(&c->commit_sem);
	if (lnum < 0)
		return lnum;

	/* GC freed one LEB, return it to lprops */
	dbg_budg("GC freed LEB %d", lnum);
	err = ubifs_return_leb(c, lnum);
	if (err)
		return err;
	return 0;
}