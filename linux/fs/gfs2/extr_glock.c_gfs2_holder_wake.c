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
struct gfs2_sbd {int /*<<< orphan*/  sd_async_glock_wait; } ;
struct gfs2_holder {int gh_flags; TYPE_2__* gh_gl; int /*<<< orphan*/  gh_iflags; } ;
struct TYPE_3__ {struct gfs2_sbd* ln_sbd; } ;
struct TYPE_4__ {TYPE_1__ gl_name; } ;

/* Variables and functions */
 int GL_ASYNC ; 
 int /*<<< orphan*/  HIF_WAIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfs2_holder_wake(struct gfs2_holder *gh)
{
	clear_bit(HIF_WAIT, &gh->gh_iflags);
	smp_mb__after_atomic();
	wake_up_bit(&gh->gh_iflags, HIF_WAIT);
	if (gh->gh_flags & GL_ASYNC) {
		struct gfs2_sbd *sdp = gh->gh_gl->gl_name.ln_sbd;

		wake_up(&sdp->sd_async_glock_wait);
	}
}