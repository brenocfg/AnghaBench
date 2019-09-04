#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ls_ops; } ;
struct gfs2_sbd {TYPE_2__ sd_lockstruct; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {struct gfs2_sbd* ln_sbd; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_holders; TYPE_4__ gl_lockref; TYPE_3__ gl_name; } ;
struct address_space {scalar_t__ nrpages; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* lm_put_lock ) (struct gfs2_glock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GLOCK_BUG_ON (struct gfs2_glock*,int) ; 
 struct address_space* gfs2_glock2aspace (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_glock_remove_from_lru (struct gfs2_glock*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockref_mark_dead (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct gfs2_glock*) ; 
 int /*<<< orphan*/  trace_gfs2_glock_put (struct gfs2_glock*) ; 

__attribute__((used)) static void __gfs2_glock_put(struct gfs2_glock *gl)
{
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	struct address_space *mapping = gfs2_glock2aspace(gl);

	lockref_mark_dead(&gl->gl_lockref);

	gfs2_glock_remove_from_lru(gl);
	spin_unlock(&gl->gl_lockref.lock);
	GLOCK_BUG_ON(gl, !list_empty(&gl->gl_holders));
	GLOCK_BUG_ON(gl, mapping && mapping->nrpages);
	trace_gfs2_glock_put(gl);
	sdp->sd_lockstruct.ls_ops->lm_put_lock(gl);
}