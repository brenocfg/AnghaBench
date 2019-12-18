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
struct gfs2_glock {int /*<<< orphan*/  gl_lockref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOCK_BUG_ON (struct gfs2_glock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lockref_is_dead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockref_get (int /*<<< orphan*/ *) ; 

void gfs2_glock_hold(struct gfs2_glock *gl)
{
	GLOCK_BUG_ON(gl, __lockref_is_dead(&gl->gl_lockref));
	lockref_get(&gl->gl_lockref);
}