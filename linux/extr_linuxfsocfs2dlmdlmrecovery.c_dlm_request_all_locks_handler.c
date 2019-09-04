#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct o2net_msg {scalar_t__ buf; } ;
struct TYPE_5__ {scalar_t__ dead_node; int /*<<< orphan*/  reco_master; } ;
struct TYPE_6__ {TYPE_2__ ral; } ;
struct dlm_work_item {int /*<<< orphan*/  list; TYPE_3__ u; } ;
struct dlm_lock_request {scalar_t__ dead_node; int /*<<< orphan*/  node_idx; } ;
struct TYPE_4__ {scalar_t__ dead_node; } ;
struct dlm_ctxt {int /*<<< orphan*/  dispatched_work; int /*<<< orphan*/  dlm_worker; int /*<<< orphan*/  work_lock; int /*<<< orphan*/  work_list; TYPE_1__ reco; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_grab (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_init_work_item (struct dlm_ctxt*,struct dlm_work_item*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dlm_print_reco_node_status (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_put (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_request_all_locks_worker ; 
 int /*<<< orphan*/  kfree (struct dlm_work_item*) ; 
 struct dlm_work_item* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_request_all_locks_handler(struct o2net_msg *msg, u32 len, void *data,
				  void **ret_data)
{
	struct dlm_ctxt *dlm = data;
	struct dlm_lock_request *lr = (struct dlm_lock_request *)msg->buf;
	char *buf = NULL;
	struct dlm_work_item *item = NULL;

	if (!dlm_grab(dlm))
		return -EINVAL;

	if (lr->dead_node != dlm->reco.dead_node) {
		mlog(ML_ERROR, "%s: node %u sent dead_node=%u, but local "
		     "dead_node is %u\n", dlm->name, lr->node_idx,
		     lr->dead_node, dlm->reco.dead_node);
		dlm_print_reco_node_status(dlm);
		/* this is a hack */
		dlm_put(dlm);
		return -ENOMEM;
	}
	BUG_ON(lr->dead_node != dlm->reco.dead_node);

	item = kzalloc(sizeof(*item), GFP_NOFS);
	if (!item) {
		dlm_put(dlm);
		return -ENOMEM;
	}

	/* this will get freed by dlm_request_all_locks_worker */
	buf = (char *) __get_free_page(GFP_NOFS);
	if (!buf) {
		kfree(item);
		dlm_put(dlm);
		return -ENOMEM;
	}

	/* queue up work for dlm_request_all_locks_worker */
	dlm_grab(dlm);  /* get an extra ref for the work item */
	dlm_init_work_item(dlm, item, dlm_request_all_locks_worker, buf);
	item->u.ral.reco_master = lr->node_idx;
	item->u.ral.dead_node = lr->dead_node;
	spin_lock(&dlm->work_lock);
	list_add_tail(&item->list, &dlm->work_list);
	spin_unlock(&dlm->work_lock);
	queue_work(dlm->dlm_worker, &dlm->dispatched_work);

	dlm_put(dlm);
	return 0;
}