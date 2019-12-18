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
struct kqid {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct TYPE_2__ {int count; int /*<<< orphan*/  lock; } ;
struct gfs2_quota_data {int qd_slot; unsigned int qd_hash; int /*<<< orphan*/  qd_gl; int /*<<< orphan*/  qd_lru; struct kqid qd_id; TYPE_1__ qd_lockref; struct gfs2_sbd* qd_sbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int gfs2_glock_get (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_quota_glops ; 
 int /*<<< orphan*/  gfs2_quotad_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct gfs2_quota_data*) ; 
 struct gfs2_quota_data* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qd2index (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gfs2_quota_data *qd_alloc(unsigned hash, struct gfs2_sbd *sdp, struct kqid qid)
{
	struct gfs2_quota_data *qd;
	int error;

	qd = kmem_cache_zalloc(gfs2_quotad_cachep, GFP_NOFS);
	if (!qd)
		return NULL;

	qd->qd_sbd = sdp;
	qd->qd_lockref.count = 1;
	spin_lock_init(&qd->qd_lockref.lock);
	qd->qd_id = qid;
	qd->qd_slot = -1;
	INIT_LIST_HEAD(&qd->qd_lru);
	qd->qd_hash = hash;

	error = gfs2_glock_get(sdp, qd2index(qd),
			      &gfs2_quota_glops, CREATE, &qd->qd_gl);
	if (error)
		goto fail;

	return qd;

fail:
	kmem_cache_free(gfs2_quotad_cachep, qd);
	return NULL;
}