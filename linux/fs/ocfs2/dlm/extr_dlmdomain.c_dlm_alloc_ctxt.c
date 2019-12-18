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
typedef  int /*<<< orphan*/  u32 ;
struct hlist_head {int dummy; } ;
struct TYPE_2__ {void* dead_node; void* new_master; int /*<<< orphan*/  event; scalar_t__ state; int /*<<< orphan*/  node_data; int /*<<< orphan*/  resources; } ;
struct dlm_ctxt {struct dlm_ctxt* name; struct hlist_head** lockres_hash; struct hlist_head** master_hash; int /*<<< orphan*/  dlm_refs; int /*<<< orphan*/  dlm_eviction_callbacks; int /*<<< orphan*/  dlm_state; int /*<<< orphan*/  dispatched_work; int /*<<< orphan*/  work_list; int /*<<< orphan*/  work_lock; int /*<<< orphan*/ * mle_cur_count; int /*<<< orphan*/ * mle_tot_count; int /*<<< orphan*/  res_cur_count; int /*<<< orphan*/  res_tot_count; TYPE_1__ reco; scalar_t__ migrate_done; int /*<<< orphan*/  dlm_join_events; int /*<<< orphan*/  joining_node; int /*<<< orphan*/  mle_hb_events; int /*<<< orphan*/  migration_wq; int /*<<< orphan*/  ast_wq; int /*<<< orphan*/  dlm_reco_thread_wq; int /*<<< orphan*/  dlm_thread_wq; int /*<<< orphan*/ * dlm_worker; int /*<<< orphan*/ * dlm_reco_thread_task; int /*<<< orphan*/ * dlm_thread_task; int /*<<< orphan*/ * domain_map; int /*<<< orphan*/ * live_nodes_map; int /*<<< orphan*/ * recovery_map; int /*<<< orphan*/  pending_basts; int /*<<< orphan*/  pending_asts; int /*<<< orphan*/  tracking_list; int /*<<< orphan*/  dlm_domain_handlers; int /*<<< orphan*/  purge_list; int /*<<< orphan*/  dirty_list; int /*<<< orphan*/  list; int /*<<< orphan*/  track_lock; int /*<<< orphan*/  ast_lock; int /*<<< orphan*/  master_lock; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  node_num; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_CTXT_NEW ; 
 int DLM_HASH_BUCKETS ; 
 int /*<<< orphan*/  DLM_HASH_PAGES ; 
 int /*<<< orphan*/  DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int DLM_MLE_NUM_TYPES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* O2NM_INVALID_NODE_NUM ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dlm_alloc_pagevec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_create_debugfs_subroot (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_dispatch_work ; 
 int /*<<< orphan*/  dlm_free_pagevec (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_lockres_hash (struct dlm_ctxt*,int) ; 
 int /*<<< orphan*/  dlm_master_hash (struct dlm_ctxt*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_read (int /*<<< orphan*/ *) ; 
 struct dlm_ctxt* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct dlm_ctxt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  o2nm_this_node () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dlm_ctxt *dlm_alloc_ctxt(const char *domain,
				u32 key)
{
	int i;
	int ret;
	struct dlm_ctxt *dlm = NULL;

	dlm = kzalloc(sizeof(*dlm), GFP_KERNEL);
	if (!dlm) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto leave;
	}

	dlm->name = kstrdup(domain, GFP_KERNEL);
	if (dlm->name == NULL) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto leave;
	}

	dlm->lockres_hash = (struct hlist_head **)dlm_alloc_pagevec(DLM_HASH_PAGES);
	if (!dlm->lockres_hash) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto leave;
	}

	for (i = 0; i < DLM_HASH_BUCKETS; i++)
		INIT_HLIST_HEAD(dlm_lockres_hash(dlm, i));

	dlm->master_hash = (struct hlist_head **)
				dlm_alloc_pagevec(DLM_HASH_PAGES);
	if (!dlm->master_hash) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto leave;
	}

	for (i = 0; i < DLM_HASH_BUCKETS; i++)
		INIT_HLIST_HEAD(dlm_master_hash(dlm, i));

	dlm->key = key;
	dlm->node_num = o2nm_this_node();

	dlm_create_debugfs_subroot(dlm);

	spin_lock_init(&dlm->spinlock);
	spin_lock_init(&dlm->master_lock);
	spin_lock_init(&dlm->ast_lock);
	spin_lock_init(&dlm->track_lock);
	INIT_LIST_HEAD(&dlm->list);
	INIT_LIST_HEAD(&dlm->dirty_list);
	INIT_LIST_HEAD(&dlm->reco.resources);
	INIT_LIST_HEAD(&dlm->reco.node_data);
	INIT_LIST_HEAD(&dlm->purge_list);
	INIT_LIST_HEAD(&dlm->dlm_domain_handlers);
	INIT_LIST_HEAD(&dlm->tracking_list);
	dlm->reco.state = 0;

	INIT_LIST_HEAD(&dlm->pending_asts);
	INIT_LIST_HEAD(&dlm->pending_basts);

	mlog(0, "dlm->recovery_map=%p, &(dlm->recovery_map[0])=%p\n",
		  dlm->recovery_map, &(dlm->recovery_map[0]));

	memset(dlm->recovery_map, 0, sizeof(dlm->recovery_map));
	memset(dlm->live_nodes_map, 0, sizeof(dlm->live_nodes_map));
	memset(dlm->domain_map, 0, sizeof(dlm->domain_map));

	dlm->dlm_thread_task = NULL;
	dlm->dlm_reco_thread_task = NULL;
	dlm->dlm_worker = NULL;
	init_waitqueue_head(&dlm->dlm_thread_wq);
	init_waitqueue_head(&dlm->dlm_reco_thread_wq);
	init_waitqueue_head(&dlm->reco.event);
	init_waitqueue_head(&dlm->ast_wq);
	init_waitqueue_head(&dlm->migration_wq);
	INIT_LIST_HEAD(&dlm->mle_hb_events);

	dlm->joining_node = DLM_LOCK_RES_OWNER_UNKNOWN;
	init_waitqueue_head(&dlm->dlm_join_events);

	dlm->migrate_done = 0;

	dlm->reco.new_master = O2NM_INVALID_NODE_NUM;
	dlm->reco.dead_node = O2NM_INVALID_NODE_NUM;

	atomic_set(&dlm->res_tot_count, 0);
	atomic_set(&dlm->res_cur_count, 0);
	for (i = 0; i < DLM_MLE_NUM_TYPES; ++i) {
		atomic_set(&dlm->mle_tot_count[i], 0);
		atomic_set(&dlm->mle_cur_count[i], 0);
	}

	spin_lock_init(&dlm->work_lock);
	INIT_LIST_HEAD(&dlm->work_list);
	INIT_WORK(&dlm->dispatched_work, dlm_dispatch_work);

	kref_init(&dlm->dlm_refs);
	dlm->dlm_state = DLM_CTXT_NEW;

	INIT_LIST_HEAD(&dlm->dlm_eviction_callbacks);

	mlog(0, "context init: refcount %u\n",
		  kref_read(&dlm->dlm_refs));

	ret = 0;
leave:
	if (ret < 0 && dlm) {
		if (dlm->master_hash)
			dlm_free_pagevec((void **)dlm->master_hash,
					DLM_HASH_PAGES);

		if (dlm->lockres_hash)
			dlm_free_pagevec((void **)dlm->lockres_hash,
					DLM_HASH_PAGES);

		kfree(dlm->name);
		kfree(dlm);
		dlm = NULL;
	}
	return dlm;
}