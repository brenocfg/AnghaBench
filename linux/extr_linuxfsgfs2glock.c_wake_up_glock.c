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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct gfs2_glock {int /*<<< orphan*/  gl_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_NORMAL ; 
 int /*<<< orphan*/  __wake_up (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * glock_waitqueue (int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wake_up_glock(struct gfs2_glock *gl)
{
	wait_queue_head_t *wq = glock_waitqueue(&gl->gl_name);

	if (waitqueue_active(wq))
		__wake_up(wq, TASK_NORMAL, 1, &gl->gl_name);
}