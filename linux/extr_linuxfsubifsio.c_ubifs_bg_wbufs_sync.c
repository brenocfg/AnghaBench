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
struct ubifs_wbuf {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  jhead; int /*<<< orphan*/  need_sync; } ;
struct ubifs_info {int jhead_cnt; TYPE_1__* jheads; scalar_t__ ro_error; scalar_t__ need_wbuf_sync; int /*<<< orphan*/  ro_mount; int /*<<< orphan*/  ro_media; } ;
struct TYPE_2__ {struct ubifs_wbuf wbuf; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  cancel_wbuf_timer_nolock (struct ubifs_wbuf*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dbg_io (char*) ; 
 scalar_t__ mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 
 int ubifs_wbuf_sync_nolock (struct ubifs_wbuf*) ; 

int ubifs_bg_wbufs_sync(struct ubifs_info *c)
{
	int err, i;

	ubifs_assert(c, !c->ro_media && !c->ro_mount);
	if (!c->need_wbuf_sync)
		return 0;
	c->need_wbuf_sync = 0;

	if (c->ro_error) {
		err = -EROFS;
		goto out_timers;
	}

	dbg_io("synchronize");
	for (i = 0; i < c->jhead_cnt; i++) {
		struct ubifs_wbuf *wbuf = &c->jheads[i].wbuf;

		cond_resched();

		/*
		 * If the mutex is locked then wbuf is being changed, so
		 * synchronization is not necessary.
		 */
		if (mutex_is_locked(&wbuf->io_mutex))
			continue;

		mutex_lock_nested(&wbuf->io_mutex, wbuf->jhead);
		if (!wbuf->need_sync) {
			mutex_unlock(&wbuf->io_mutex);
			continue;
		}

		err = ubifs_wbuf_sync_nolock(wbuf);
		mutex_unlock(&wbuf->io_mutex);
		if (err) {
			ubifs_err(c, "cannot sync write-buffer, error %d", err);
			ubifs_ro_mode(c, err);
			goto out_timers;
		}
	}

	return 0;

out_timers:
	/* Cancel all timers to prevent repeated errors */
	for (i = 0; i < c->jhead_cnt; i++) {
		struct ubifs_wbuf *wbuf = &c->jheads[i].wbuf;

		mutex_lock_nested(&wbuf->io_mutex, wbuf->jhead);
		cancel_wbuf_timer_nolock(wbuf);
		mutex_unlock(&wbuf->io_mutex);
	}
	return err;
}