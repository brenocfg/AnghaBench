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
struct gfs2_sbd {int /*<<< orphan*/  sd_glock_wait; int /*<<< orphan*/  sd_glock_disposal; } ;
struct TYPE_2__ {struct gfs2_sbd* ln_sbd; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_rcu; int /*<<< orphan*/  gl_node; int /*<<< orphan*/  gl_revokes; TYPE_1__ gl_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dealloc ; 
 int /*<<< orphan*/  gl_hash_table ; 
 int /*<<< orphan*/  ht_parms ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_glock (struct gfs2_glock*) ; 

void gfs2_glock_free(struct gfs2_glock *gl)
{
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;

	BUG_ON(atomic_read(&gl->gl_revokes));
	rhashtable_remove_fast(&gl_hash_table, &gl->gl_node, ht_parms);
	smp_mb();
	wake_up_glock(gl);
	call_rcu(&gl->gl_rcu, gfs2_glock_dealloc);
	if (atomic_dec_and_test(&sdp->sd_glock_disposal))
		wake_up(&sdp->sd_glock_wait);
}