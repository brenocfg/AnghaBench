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
struct kqid {int dummy; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_quota_count; int /*<<< orphan*/  sd_quota_list; } ;
struct gfs2_quota_data {int /*<<< orphan*/  qd_gl; int /*<<< orphan*/  qd_hlist; int /*<<< orphan*/  qd_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_glock_put (int /*<<< orphan*/ ) ; 
 unsigned int gfs2_qd_hash (struct gfs2_sbd*,struct kqid) ; 
 struct gfs2_quota_data* gfs2_qd_search_bucket (unsigned int,struct gfs2_sbd*,struct kqid) ; 
 int /*<<< orphan*/  gfs2_quotad_cachep ; 
 int /*<<< orphan*/  hlist_bl_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct gfs2_quota_data* qd_alloc (unsigned int,struct gfs2_sbd*,struct kqid) ; 
 int /*<<< orphan*/ * qd_hash_table ; 
 int /*<<< orphan*/  qd_lock ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bucket (unsigned int) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bucket (unsigned int) ; 

__attribute__((used)) static int qd_get(struct gfs2_sbd *sdp, struct kqid qid,
		  struct gfs2_quota_data **qdp)
{
	struct gfs2_quota_data *qd, *new_qd;
	unsigned int hash = gfs2_qd_hash(sdp, qid);

	rcu_read_lock();
	*qdp = qd = gfs2_qd_search_bucket(hash, sdp, qid);
	rcu_read_unlock();

	if (qd)
		return 0;

	new_qd = qd_alloc(hash, sdp, qid);
	if (!new_qd)
		return -ENOMEM;

	spin_lock(&qd_lock);
	spin_lock_bucket(hash);
	*qdp = qd = gfs2_qd_search_bucket(hash, sdp, qid);
	if (qd == NULL) {
		*qdp = new_qd;
		list_add(&new_qd->qd_list, &sdp->sd_quota_list);
		hlist_bl_add_head_rcu(&new_qd->qd_hlist, &qd_hash_table[hash]);
		atomic_inc(&sdp->sd_quota_count);
	}
	spin_unlock_bucket(hash);
	spin_unlock(&qd_lock);

	if (qd) {
		gfs2_glock_put(new_qd->qd_gl);
		kmem_cache_free(gfs2_quotad_cachep, new_qd);
	}

	return 0;
}