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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct gfs2_glock {scalar_t__ gl_state; TYPE_1__ gl_lockref; } ;

/* Variables and functions */
 scalar_t__ LM_ST_UNLOCKED ; 
 int /*<<< orphan*/  __gfs2_glock_queue_work (struct gfs2_glock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_remove_from_lru (struct gfs2_glock*) ; 
 int /*<<< orphan*/  handle_callback (struct gfs2_glock*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_glock(struct gfs2_glock *gl)
{
	gfs2_glock_remove_from_lru(gl);

	spin_lock(&gl->gl_lockref.lock);
	if (gl->gl_state != LM_ST_UNLOCKED)
		handle_callback(gl, LM_ST_UNLOCKED, 0, false);
	__gfs2_glock_queue_work(gl, 0);
	spin_unlock(&gl->gl_lockref.lock);
}