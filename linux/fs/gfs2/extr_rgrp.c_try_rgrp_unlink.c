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
typedef  scalar_t__ u64 ;
struct gfs2_sbd {int /*<<< orphan*/  sd_log_flush_lock; } ;
struct gfs2_rgrpd {int /*<<< orphan*/  rd_flags; struct gfs2_sbd* rd_sbd; } ;
struct gfs2_rbm {int /*<<< orphan*/  offset; int /*<<< orphan*/  bii; struct gfs2_rgrpd* rgd; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_delete; struct gfs2_inode* gl_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFS2_BLKST_UNLINKED ; 
 int /*<<< orphan*/  GFS2_RDF_CHECK ; 
 scalar_t__ NO_BLOCK ; 
 int NR_CPUS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_delete_workqueue ; 
 int gfs2_glock_get (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gfs2_glock**) ; 
 int /*<<< orphan*/  gfs2_glock_put (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_iopen_glops ; 
 int gfs2_rbm_find (struct gfs2_rbm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ gfs2_rbm_from_block (struct gfs2_rbm*,scalar_t__) ; 
 scalar_t__ gfs2_rbm_to_block (struct gfs2_rbm*) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void try_rgrp_unlink(struct gfs2_rgrpd *rgd, u64 *last_unlinked, u64 skip)
{
	u64 block;
	struct gfs2_sbd *sdp = rgd->rd_sbd;
	struct gfs2_glock *gl;
	struct gfs2_inode *ip;
	int error;
	int found = 0;
	struct gfs2_rbm rbm = { .rgd = rgd, .bii = 0, .offset = 0 };

	while (1) {
		down_write(&sdp->sd_log_flush_lock);
		error = gfs2_rbm_find(&rbm, GFS2_BLKST_UNLINKED, NULL, NULL,
				      true);
		up_write(&sdp->sd_log_flush_lock);
		if (error == -ENOSPC)
			break;
		if (WARN_ON_ONCE(error))
			break;

		block = gfs2_rbm_to_block(&rbm);
		if (gfs2_rbm_from_block(&rbm, block + 1))
			break;
		if (*last_unlinked != NO_BLOCK && block <= *last_unlinked)
			continue;
		if (block == skip)
			continue;
		*last_unlinked = block;

		error = gfs2_glock_get(sdp, block, &gfs2_iopen_glops, CREATE, &gl);
		if (error)
			continue;

		/* If the inode is already in cache, we can ignore it here
		 * because the existing inode disposal code will deal with
		 * it when all refs have gone away. Accessing gl_object like
		 * this is not safe in general. Here it is ok because we do
		 * not dereference the pointer, and we only need an approx
		 * answer to whether it is NULL or not.
		 */
		ip = gl->gl_object;

		if (ip || queue_work(gfs2_delete_workqueue, &gl->gl_delete) == 0)
			gfs2_glock_put(gl);
		else
			found++;

		/* Limit reclaim to sensible number of tasks */
		if (found > NR_CPUS)
			return;
	}

	rgd->rd_flags &= ~GFS2_RDF_CHECK;
	return;
}