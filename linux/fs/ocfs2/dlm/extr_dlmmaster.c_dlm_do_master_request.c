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
struct dlm_master_request {scalar_t__ namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  node_idx; } ;
struct dlm_master_list_entry {scalar_t__ type; int master; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  maybe_map; int /*<<< orphan*/  response_map; int /*<<< orphan*/  mname; scalar_t__ mnamelen; struct dlm_ctxt* dlm; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  key; int /*<<< orphan*/  node_num; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DLM_MASTER_REQUEST_MSG ; 
#define  DLM_MASTER_RESP_ERROR 131 
#define  DLM_MASTER_RESP_MAYBE 130 
#define  DLM_MASTER_RESP_NO 129 
#define  DLM_MASTER_RESP_YES 128 
 scalar_t__ DLM_MLE_MIGRATION ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  dlm_is_host_down (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct dlm_master_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_master_request*,int,int,int*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_do_master_request(struct dlm_lock_resource *res,
				 struct dlm_master_list_entry *mle, int to)
{
	struct dlm_ctxt *dlm = mle->dlm;
	struct dlm_master_request request;
	int ret, response=0, resend;

	memset(&request, 0, sizeof(request));
	request.node_idx = dlm->node_num;

	BUG_ON(mle->type == DLM_MLE_MIGRATION);

	request.namelen = (u8)mle->mnamelen;
	memcpy(request.name, mle->mname, request.namelen);

again:
	ret = o2net_send_message(DLM_MASTER_REQUEST_MSG, dlm->key, &request,
				 sizeof(request), to, &response);
	if (ret < 0)  {
		if (ret == -ESRCH) {
			/* should never happen */
			mlog(ML_ERROR, "TCP stack not ready!\n");
			BUG();
		} else if (ret == -EINVAL) {
			mlog(ML_ERROR, "bad args passed to o2net!\n");
			BUG();
		} else if (ret == -ENOMEM) {
			mlog(ML_ERROR, "out of memory while trying to send "
			     "network message!  retrying\n");
			/* this is totally crude */
			msleep(50);
			goto again;
		} else if (!dlm_is_host_down(ret)) {
			/* not a network error. bad. */
			mlog_errno(ret);
			mlog(ML_ERROR, "unhandled error!");
			BUG();
		}
		/* all other errors should be network errors,
		 * and likely indicate node death */
		mlog(ML_ERROR, "link to %d went down!\n", to);
		goto out;
	}

	ret = 0;
	resend = 0;
	spin_lock(&mle->spinlock);
	switch (response) {
		case DLM_MASTER_RESP_YES:
			set_bit(to, mle->response_map);
			mlog(0, "node %u is the master, response=YES\n", to);
			mlog(0, "%s:%.*s: master node %u now knows I have a "
			     "reference\n", dlm->name, res->lockname.len,
			     res->lockname.name, to);
			mle->master = to;
			break;
		case DLM_MASTER_RESP_NO:
			mlog(0, "node %u not master, response=NO\n", to);
			set_bit(to, mle->response_map);
			break;
		case DLM_MASTER_RESP_MAYBE:
			mlog(0, "node %u not master, response=MAYBE\n", to);
			set_bit(to, mle->response_map);
			set_bit(to, mle->maybe_map);
			break;
		case DLM_MASTER_RESP_ERROR:
			mlog(0, "node %u hit an error, resending\n", to);
			resend = 1;
			response = 0;
			break;
		default:
			mlog(ML_ERROR, "bad response! %u\n", response);
			BUG();
	}
	spin_unlock(&mle->spinlock);
	if (resend) {
		/* this is also totally crude */
		msleep(50);
		goto again;
	}

out:
	return ret;
}