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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  ln_sbd; } ;
struct gfs2_glock {TYPE_2__ gl_lockref; int /*<<< orphan*/ * gl_object; TYPE_1__ gl_name; } ;

/* Variables and functions */
 scalar_t__ gfs2_assert_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_dump_glock (int /*<<< orphan*/ *,struct gfs2_glock*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void glock_set_object(struct gfs2_glock *gl, void *object)
{
	spin_lock(&gl->gl_lockref.lock);
	if (gfs2_assert_warn(gl->gl_name.ln_sbd, gl->gl_object == NULL))
		gfs2_dump_glock(NULL, gl, true);
	gl->gl_object = object;
	spin_unlock(&gl->gl_lockref.lock);
}