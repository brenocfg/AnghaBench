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
 int /*<<< orphan*/  __gfs2_glock_put (struct gfs2_glock*) ; 
 scalar_t__ lockref_put_or_lock (int /*<<< orphan*/ *) ; 

void gfs2_glock_put(struct gfs2_glock *gl)
{
	if (lockref_put_or_lock(&gl->gl_lockref))
		return;

	__gfs2_glock_put(gl);
}