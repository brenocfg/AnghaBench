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
struct zfcp_fsf_req {int status; struct zfcp_erp_action* erp_action; } ;
struct zfcp_erp_action {int status; int /*<<< orphan*/  fsf_req_id; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {TYPE_1__* req_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ZFCP_STATUS_ERP_DISMISSED ; 
 int ZFCP_STATUS_ERP_TIMEDOUT ; 
 int ZFCP_STATUS_FSFREQ_DISMISSED ; 
 struct zfcp_fsf_req* _zfcp_reqlist_find (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_run (char*,struct zfcp_erp_action*) ; 

__attribute__((used)) static void zfcp_erp_strategy_check_fsfreq(struct zfcp_erp_action *act)
{
	struct zfcp_adapter *adapter = act->adapter;
	struct zfcp_fsf_req *req;

	if (!act->fsf_req_id)
		return;

	spin_lock(&adapter->req_list->lock);
	req = _zfcp_reqlist_find(adapter->req_list, act->fsf_req_id);
	if (req && req->erp_action == act) {
		if (act->status & (ZFCP_STATUS_ERP_DISMISSED |
				   ZFCP_STATUS_ERP_TIMEDOUT)) {
			req->status |= ZFCP_STATUS_FSFREQ_DISMISSED;
			zfcp_dbf_rec_run("erscf_1", act);
			req->erp_action = NULL;
		}
		if (act->status & ZFCP_STATUS_ERP_TIMEDOUT)
			zfcp_dbf_rec_run("erscf_2", act);
		if (req->status & ZFCP_STATUS_FSFREQ_DISMISSED)
			act->fsf_req_id = 0;
	} else
		act->fsf_req_id = 0;
	spin_unlock(&adapter->req_list->lock);
}