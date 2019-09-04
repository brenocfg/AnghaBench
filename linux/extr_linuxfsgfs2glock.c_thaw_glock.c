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
struct gfs2_glock {int /*<<< orphan*/  gl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLF_FROZEN ; 
 int /*<<< orphan*/  GLF_REPLY_PENDING ; 
 int /*<<< orphan*/  gfs2_glock_put (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_glock_queue_work (struct gfs2_glock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thaw_glock(struct gfs2_glock *gl)
{
	if (!test_and_clear_bit(GLF_FROZEN, &gl->gl_flags)) {
		gfs2_glock_put(gl);
		return;
	}
	set_bit(GLF_REPLY_PENDING, &gl->gl_flags);
	gfs2_glock_queue_work(gl, 0);
}