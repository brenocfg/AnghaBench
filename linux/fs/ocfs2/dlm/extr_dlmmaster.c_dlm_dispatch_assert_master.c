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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int ignore_higher; int /*<<< orphan*/  flags; int /*<<< orphan*/  request_from; struct dlm_lock_resource* lockres; } ;
struct TYPE_5__ {TYPE_1__ am; } ;
struct dlm_work_item {int /*<<< orphan*/  list; TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {TYPE_3__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  dispatched_work; int /*<<< orphan*/  dlm_worker; int /*<<< orphan*/  work_lock; int /*<<< orphan*/  work_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dlm_assert_master_worker ; 
 int /*<<< orphan*/  dlm_init_work_item (struct dlm_ctxt*,struct dlm_work_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dlm_work_item* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_dispatch_assert_master(struct dlm_ctxt *dlm,
			       struct dlm_lock_resource *res,
			       int ignore_higher, u8 request_from, u32 flags)
{
	struct dlm_work_item *item;
	item = kzalloc(sizeof(*item), GFP_ATOMIC);
	if (!item)
		return -ENOMEM;


	/* queue up work for dlm_assert_master_worker */
	dlm_init_work_item(dlm, item, dlm_assert_master_worker, NULL);
	item->u.am.lockres = res; /* already have a ref */
	/* can optionally ignore node numbers higher than this node */
	item->u.am.ignore_higher = ignore_higher;
	item->u.am.request_from = request_from;
	item->u.am.flags = flags;

	if (ignore_higher)
		mlog(0, "IGNORE HIGHER: %.*s\n", res->lockname.len,
		     res->lockname.name);

	spin_lock(&dlm->work_lock);
	list_add_tail(&item->list, &dlm->work_list);
	spin_unlock(&dlm->work_lock);

	queue_work(dlm->dlm_worker, &dlm->dispatched_work);
	return 0;
}