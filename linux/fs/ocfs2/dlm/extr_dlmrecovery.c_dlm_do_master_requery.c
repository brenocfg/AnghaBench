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
typedef  scalar_t__ u8 ;
struct dlm_master_requery {int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; int /*<<< orphan*/  node_idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dlm_lock_resource {TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  key; int /*<<< orphan*/  node_num; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int /*<<< orphan*/  DLM_MASTER_REQUERY_MSG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dlm_master_requery*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,scalar_t__,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_master_requery*,int,scalar_t__,int*) ; 

int dlm_do_master_requery(struct dlm_ctxt *dlm, struct dlm_lock_resource *res,
			  u8 nodenum, u8 *real_master)
{
	int ret = -EINVAL;
	struct dlm_master_requery req;
	int status = DLM_LOCK_RES_OWNER_UNKNOWN;

	memset(&req, 0, sizeof(req));
	req.node_idx = dlm->node_num;
	req.namelen = res->lockname.len;
	memcpy(req.name, res->lockname.name, res->lockname.len);

resend:
	ret = o2net_send_message(DLM_MASTER_REQUERY_MSG, dlm->key,
				 &req, sizeof(req), nodenum, &status);
	if (ret < 0)
		mlog(ML_ERROR, "Error %d when sending message %u (key "
		     "0x%x) to node %u\n", ret, DLM_MASTER_REQUERY_MSG,
		     dlm->key, nodenum);
	else if (status == -ENOMEM) {
		mlog_errno(status);
		msleep(50);
		goto resend;
	} else {
		BUG_ON(status < 0);
		BUG_ON(status > DLM_LOCK_RES_OWNER_UNKNOWN);
		*real_master = (u8) (status & 0xff);
		mlog(0, "node %u responded to master requery with %u\n",
			  nodenum, *real_master);
		ret = 0;
	}
	return ret;
}