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
struct TYPE_2__ {int count; } ;
struct gfs2_glock {TYPE_1__ gl_lockref; int /*<<< orphan*/  gl_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOCK_BUG_ON (struct gfs2_glock*,int) ; 
 int /*<<< orphan*/  glock_workqueue ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __gfs2_glock_queue_work(struct gfs2_glock *gl, unsigned long delay) {
	if (!queue_delayed_work(glock_workqueue, &gl->gl_work, delay)) {
		/*
		 * We are holding the lockref spinlock, and the work was still
		 * queued above.  The queued work (glock_work_func) takes that
		 * spinlock before dropping its glock reference(s), so it
		 * cannot have dropped them in the meantime.
		 */
		GLOCK_BUG_ON(gl, gl->gl_lockref.count < 2);
		gl->gl_lockref.count--;
	}
}