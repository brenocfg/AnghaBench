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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int ignore_higher; int request_from; int /*<<< orphan*/  flags; struct dlm_lock_resource* lockres; } ;
struct TYPE_5__ {TYPE_1__ am; } ;
struct dlm_work_item {TYPE_2__ u; struct dlm_ctxt* dlm; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {int state; TYPE_3__ lockname; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int node_num; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; } ;
typedef  int /*<<< orphan*/  nodemap ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int DLM_LOCK_RES_MIGRATING ; 
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  __dlm_lockres_reserve_ast (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int dlm_do_assert_master (struct dlm_ctxt*,struct dlm_lock_resource*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_is_host_down (int) ; 
 int /*<<< orphan*/  dlm_lockres_drop_inflight_worker (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_release_ast (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int find_next_bit (unsigned long*,int,int) ; 
 int /*<<< orphan*/  memcpy (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_assert_master_worker(struct dlm_work_item *item, void *data)
{
	struct dlm_ctxt *dlm = data;
	int ret = 0;
	struct dlm_lock_resource *res;
	unsigned long nodemap[BITS_TO_LONGS(O2NM_MAX_NODES)];
	int ignore_higher;
	int bit;
	u8 request_from;
	u32 flags;

	dlm = item->dlm;
	res = item->u.am.lockres;
	ignore_higher = item->u.am.ignore_higher;
	request_from = item->u.am.request_from;
	flags = item->u.am.flags;

	spin_lock(&dlm->spinlock);
	memcpy(nodemap, dlm->domain_map, sizeof(nodemap));
	spin_unlock(&dlm->spinlock);

	clear_bit(dlm->node_num, nodemap);
	if (ignore_higher) {
		/* if is this just to clear up mles for nodes below
		 * this node, do not send the message to the original
		 * caller or any node number higher than this */
		clear_bit(request_from, nodemap);
		bit = dlm->node_num;
		while (1) {
			bit = find_next_bit(nodemap, O2NM_MAX_NODES,
					    bit+1);
		       	if (bit >= O2NM_MAX_NODES)
				break;
			clear_bit(bit, nodemap);
		}
	}

	/*
	 * If we're migrating this lock to someone else, we are no
	 * longer allowed to assert out own mastery.  OTOH, we need to
	 * prevent migration from starting while we're still asserting
	 * our dominance.  The reserved ast delays migration.
	 */
	spin_lock(&res->spinlock);
	if (res->state & DLM_LOCK_RES_MIGRATING) {
		mlog(0, "Someone asked us to assert mastery, but we're "
		     "in the middle of migration.  Skipping assert, "
		     "the new master will handle that.\n");
		spin_unlock(&res->spinlock);
		goto put;
	} else
		__dlm_lockres_reserve_ast(res);
	spin_unlock(&res->spinlock);

	/* this call now finishes out the nodemap
	 * even if one or more nodes die */
	mlog(0, "worker about to master %.*s here, this=%u\n",
		     res->lockname.len, res->lockname.name, dlm->node_num);
	ret = dlm_do_assert_master(dlm, res, nodemap, flags);
	if (ret < 0) {
		/* no need to restart, we are done */
		if (!dlm_is_host_down(ret))
			mlog_errno(ret);
	}

	/* Ok, we've asserted ourselves.  Let's let migration start. */
	dlm_lockres_release_ast(dlm, res);

put:
	dlm_lockres_drop_inflight_worker(dlm, res);

	dlm_lockres_put(res);

	mlog(0, "finished with dlm_assert_master_worker\n");
}