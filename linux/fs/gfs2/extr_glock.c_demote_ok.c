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
struct gfs2_glock_operations {int (* go_demote_ok ) (struct gfs2_glock const*) ;} ;
struct gfs2_glock {scalar_t__ gl_state; int /*<<< orphan*/  gl_holders; struct gfs2_glock_operations* gl_ops; } ;

/* Variables and functions */
 scalar_t__ LM_ST_UNLOCKED ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int stub1 (struct gfs2_glock const*) ; 

__attribute__((used)) static int demote_ok(const struct gfs2_glock *gl)
{
	const struct gfs2_glock_operations *glops = gl->gl_ops;

	if (gl->gl_state == LM_ST_UNLOCKED)
		return 0;
	if (!list_empty(&gl->gl_holders))
		return 0;
	if (glops->go_demote_ok)
		return glops->go_demote_ok(gl);
	return 1;
}