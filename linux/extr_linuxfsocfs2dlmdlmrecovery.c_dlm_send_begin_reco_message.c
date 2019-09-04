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
typedef  int u8 ;
struct dlm_node_iter {int /*<<< orphan*/  node_map; } ;
struct dlm_lock_resource {int dummy; } ;
struct dlm_ctxt {int node_num; int /*<<< orphan*/  name; int /*<<< orphan*/  key; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; } ;
struct dlm_begin_reco {int node_idx; int dead_node; } ;
typedef  int /*<<< orphan*/  br ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_BEGIN_RECO_MSG ; 
 int /*<<< orphan*/  DLM_RECOVERY_LOCK_NAME ; 
 int /*<<< orphan*/  DLM_RECOVERY_LOCK_NAME_LEN ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ dlm_is_host_down (int) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 struct dlm_lock_resource* dlm_lookup_lockres (struct dlm_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_node_iter_init (int /*<<< orphan*/ ,struct dlm_node_iter*) ; 
 int dlm_node_iter_next (struct dlm_node_iter*) ; 
 int /*<<< orphan*/  dlm_print_one_lock_resource (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  memset (struct dlm_begin_reco*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_begin_reco*,int,int,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_send_begin_reco_message(struct dlm_ctxt *dlm, u8 dead_node)
{
	struct dlm_begin_reco br;
	int ret = 0;
	struct dlm_node_iter iter;
	int nodenum;
	int status;

	mlog(0, "%s: dead node is %u\n", dlm->name, dead_node);

	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->domain_map, &iter);
	spin_unlock(&dlm->spinlock);

	clear_bit(dead_node, iter.node_map);

	memset(&br, 0, sizeof(br));
	br.node_idx = dlm->node_num;
	br.dead_node = dead_node;

	while ((nodenum = dlm_node_iter_next(&iter)) >= 0) {
		ret = 0;
		if (nodenum == dead_node) {
			mlog(0, "not sending begin reco to dead node "
				  "%u\n", dead_node);
			continue;
		}
		if (nodenum == dlm->node_num) {
			mlog(0, "not sending begin reco to self\n");
			continue;
		}
retry:
		ret = -EINVAL;
		mlog(0, "attempting to send begin reco msg to %d\n",
			  nodenum);
		ret = o2net_send_message(DLM_BEGIN_RECO_MSG, dlm->key,
					 &br, sizeof(br), nodenum, &status);
		/* negative status is handled ok by caller here */
		if (ret >= 0)
			ret = status;
		if (dlm_is_host_down(ret)) {
			/* node is down.  not involved in recovery
			 * so just keep going */
			mlog(ML_NOTICE, "%s: node %u was down when sending "
			     "begin reco msg (%d)\n", dlm->name, nodenum, ret);
			ret = 0;
		}

		/*
		 * Prior to commit aad1b15310b9bcd59fa81ab8f2b1513b59553ea8,
		 * dlm_begin_reco_handler() returned EAGAIN and not -EAGAIN.
		 * We are handling both for compatibility reasons.
		 */
		if (ret == -EAGAIN || ret == EAGAIN) {
			mlog(0, "%s: trying to start recovery of node "
			     "%u, but node %u is waiting for last recovery "
			     "to complete, backoff for a bit\n", dlm->name,
			     dead_node, nodenum);
			msleep(100);
			goto retry;
		}
		if (ret < 0) {
			struct dlm_lock_resource *res;

			/* this is now a serious problem, possibly ENOMEM
			 * in the network stack.  must retry */
			mlog_errno(ret);
			mlog(ML_ERROR, "begin reco of dlm %s to node %u "
			     "returned %d\n", dlm->name, nodenum, ret);
			res = dlm_lookup_lockres(dlm, DLM_RECOVERY_LOCK_NAME,
						 DLM_RECOVERY_LOCK_NAME_LEN);
			if (res) {
				dlm_print_one_lock_resource(res);
				dlm_lockres_put(res);
			} else {
				mlog(ML_ERROR, "recovery lock not found\n");
			}
			/* sleep for a bit in hopes that we can avoid
			 * another ENOMEM */
			msleep(100);
			goto retry;
		}
	}

	return ret;
}