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
struct ubifs_wbuf {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  jhead; } ;
struct ubifs_info {int jhead_cnt; TYPE_1__* jheads; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {struct ubifs_wbuf wbuf; } ;

/* Variables and functions */
 int GCHD ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 
 int ubifs_wbuf_sync_nolock (struct ubifs_wbuf*) ; 
 scalar_t__ wbuf_has_ino (struct ubifs_wbuf*,int /*<<< orphan*/ ) ; 

int ubifs_sync_wbufs_by_inode(struct ubifs_info *c, struct inode *inode)
{
	int i, err = 0;

	for (i = 0; i < c->jhead_cnt; i++) {
		struct ubifs_wbuf *wbuf = &c->jheads[i].wbuf;

		if (i == GCHD)
			/*
			 * GC head is special, do not look at it. Even if the
			 * head contains something related to this inode, it is
			 * a _copy_ of corresponding on-flash node which sits
			 * somewhere else.
			 */
			continue;

		if (!wbuf_has_ino(wbuf, inode->i_ino))
			continue;

		mutex_lock_nested(&wbuf->io_mutex, wbuf->jhead);
		if (wbuf_has_ino(wbuf, inode->i_ino))
			err = ubifs_wbuf_sync_nolock(wbuf);
		mutex_unlock(&wbuf->io_mutex);

		if (err) {
			ubifs_ro_mode(c, err);
			return err;
		}
	}
	return 0;
}