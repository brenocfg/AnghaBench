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
struct dlm_master_list_entry {int type; unsigned int mnamelen; int /*<<< orphan*/  node_map; int /*<<< orphan*/  vote_map; int /*<<< orphan*/  mnamehash; int /*<<< orphan*/  mname; struct dlm_lock_resource* mleres; scalar_t__ inuse; void* new_master; void* master; int /*<<< orphan*/  response_map; int /*<<< orphan*/  mle_refs; int /*<<< orphan*/  woken; int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  maybe_map; int /*<<< orphan*/  hb_events; int /*<<< orphan*/  master_hash_node; struct dlm_ctxt* dlm; } ;
struct TYPE_2__ {char const* name; int len; int /*<<< orphan*/  hash; } ;
struct dlm_lock_resource {TYPE_1__ lockname; } ;
struct dlm_ctxt {char const* domain_map; int /*<<< orphan*/  node_num; int /*<<< orphan*/ * mle_cur_count; int /*<<< orphan*/ * mle_tot_count; int /*<<< orphan*/  spinlock; } ;
typedef  enum dlm_mle_type { ____Placeholder_dlm_mle_type } dlm_mle_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_MLE_BLOCK ; 
 int DLM_MLE_MASTER ; 
 int DLM_MLE_MIGRATION ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* O2NM_MAX_NODES ; 
 int /*<<< orphan*/  __dlm_mle_attach_hb_events (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_lockid_hash (char const*,unsigned int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_init_mle(struct dlm_master_list_entry *mle,
			enum dlm_mle_type type,
			struct dlm_ctxt *dlm,
			struct dlm_lock_resource *res,
			const char *name,
			unsigned int namelen)
{
	assert_spin_locked(&dlm->spinlock);

	mle->dlm = dlm;
	mle->type = type;
	INIT_HLIST_NODE(&mle->master_hash_node);
	INIT_LIST_HEAD(&mle->hb_events);
	memset(mle->maybe_map, 0, sizeof(mle->maybe_map));
	spin_lock_init(&mle->spinlock);
	init_waitqueue_head(&mle->wq);
	atomic_set(&mle->woken, 0);
	kref_init(&mle->mle_refs);
	memset(mle->response_map, 0, sizeof(mle->response_map));
	mle->master = O2NM_MAX_NODES;
	mle->new_master = O2NM_MAX_NODES;
	mle->inuse = 0;

	BUG_ON(mle->type != DLM_MLE_BLOCK &&
	       mle->type != DLM_MLE_MASTER &&
	       mle->type != DLM_MLE_MIGRATION);

	if (mle->type == DLM_MLE_MASTER) {
		BUG_ON(!res);
		mle->mleres = res;
		memcpy(mle->mname, res->lockname.name, res->lockname.len);
		mle->mnamelen = res->lockname.len;
		mle->mnamehash = res->lockname.hash;
	} else {
		BUG_ON(!name);
		mle->mleres = NULL;
		memcpy(mle->mname, name, namelen);
		mle->mnamelen = namelen;
		mle->mnamehash = dlm_lockid_hash(name, namelen);
	}

	atomic_inc(&dlm->mle_tot_count[mle->type]);
	atomic_inc(&dlm->mle_cur_count[mle->type]);

	/* copy off the node_map and register hb callbacks on our copy */
	memcpy(mle->node_map, dlm->domain_map, sizeof(mle->node_map));
	memcpy(mle->vote_map, dlm->domain_map, sizeof(mle->vote_map));
	clear_bit(dlm->node_num, mle->vote_map);
	clear_bit(dlm->node_num, mle->node_map);

	/* attach the mle to the domain node up/down events */
	__dlm_mle_attach_hb_events(dlm, mle);
}