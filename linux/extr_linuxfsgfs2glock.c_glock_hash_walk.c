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
struct rhashtable_iter {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct TYPE_2__ {struct gfs2_sbd const* ln_sbd; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_lockref; TYPE_1__ gl_name; } ;
typedef  int /*<<< orphan*/  (* glock_examiner ) (struct gfs2_glock*) ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct gfs2_glock* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct gfs2_glock*) ; 
 int cond_resched () ; 
 int /*<<< orphan*/  gl_hash_table ; 
 scalar_t__ lockref_get_not_dead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_walk_enter (int /*<<< orphan*/ *,struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_exit (struct rhashtable_iter*) ; 
 struct gfs2_glock* rhashtable_walk_next (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_start (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_stop (struct rhashtable_iter*) ; 

__attribute__((used)) static void glock_hash_walk(glock_examiner examiner, const struct gfs2_sbd *sdp)
{
	struct gfs2_glock *gl;
	struct rhashtable_iter iter;

	rhashtable_walk_enter(&gl_hash_table, &iter);

	do {
		rhashtable_walk_start(&iter);

		while ((gl = rhashtable_walk_next(&iter)) && !IS_ERR(gl))
			if (gl->gl_name.ln_sbd == sdp &&
			    lockref_get_not_dead(&gl->gl_lockref))
				examiner(gl);

		rhashtable_walk_stop(&iter);
	} while (cond_resched(), gl == ERR_PTR(-EAGAIN));

	rhashtable_walk_exit(&iter);
}