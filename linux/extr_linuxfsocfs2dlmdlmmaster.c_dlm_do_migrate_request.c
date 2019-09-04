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
typedef  int u8 ;
struct dlm_node_iter {int /*<<< orphan*/  node_map; } ;
struct dlm_migrate_request {int new_master; int master; int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {int /*<<< orphan*/  spinlock; TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  key; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; } ;
typedef  int /*<<< orphan*/  migrate ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DLM_MIGRATE_REQUEST_MSG ; 
 int DLM_MIGRATE_RESPONSE_MASTERY_REF ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_is_host_down (int) ; 
 int /*<<< orphan*/  dlm_lockres_set_refmap_bit (struct dlm_ctxt*,struct dlm_lock_resource*,int) ; 
 int dlm_node_iter_next (struct dlm_node_iter*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dlm_migrate_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_migrate_request*,int,int,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_do_migrate_request(struct dlm_ctxt *dlm,
				  struct dlm_lock_resource *res,
				  u8 master, u8 new_master,
				  struct dlm_node_iter *iter)
{
	struct dlm_migrate_request migrate;
	int ret, skip, status = 0;
	int nodenum;

	memset(&migrate, 0, sizeof(migrate));
	migrate.namelen = res->lockname.len;
	memcpy(migrate.name, res->lockname.name, migrate.namelen);
	migrate.new_master = new_master;
	migrate.master = master;

	ret = 0;

	/* send message to all nodes, except the master and myself */
	while ((nodenum = dlm_node_iter_next(iter)) >= 0) {
		if (nodenum == master ||
		    nodenum == new_master)
			continue;

		/* We could race exit domain. If exited, skip. */
		spin_lock(&dlm->spinlock);
		skip = (!test_bit(nodenum, dlm->domain_map));
		spin_unlock(&dlm->spinlock);
		if (skip) {
			clear_bit(nodenum, iter->node_map);
			continue;
		}

		ret = o2net_send_message(DLM_MIGRATE_REQUEST_MSG, dlm->key,
					 &migrate, sizeof(migrate), nodenum,
					 &status);
		if (ret < 0) {
			mlog(ML_ERROR, "%s: res %.*s, Error %d send "
			     "MIGRATE_REQUEST to node %u\n", dlm->name,
			     migrate.namelen, migrate.name, ret, nodenum);
			if (!dlm_is_host_down(ret)) {
				mlog(ML_ERROR, "unhandled error=%d!\n", ret);
				BUG();
			}
			clear_bit(nodenum, iter->node_map);
			ret = 0;
		} else if (status < 0) {
			mlog(0, "migrate request (node %u) returned %d!\n",
			     nodenum, status);
			ret = status;
		} else if (status == DLM_MIGRATE_RESPONSE_MASTERY_REF) {
			/* during the migration request we short-circuited
			 * the mastery of the lockres.  make sure we have
			 * a mastery ref for nodenum */
			mlog(0, "%s:%.*s: need ref for node %u\n",
			     dlm->name, res->lockname.len, res->lockname.name,
			     nodenum);
			spin_lock(&res->spinlock);
			dlm_lockres_set_refmap_bit(dlm, res, nodenum);
			spin_unlock(&res->spinlock);
		}
	}

	if (ret < 0)
		mlog_errno(ret);

	mlog(0, "returning ret=%d\n", ret);
	return ret;
}