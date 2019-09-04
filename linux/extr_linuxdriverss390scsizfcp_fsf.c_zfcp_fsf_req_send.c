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
struct zfcp_qdio {int /*<<< orphan*/  req_q_free; } ;
struct TYPE_2__ {int /*<<< orphan*/  qdio_outb_usage; } ;
struct zfcp_fsf_req {int req_id; int /*<<< orphan*/  timer; TYPE_1__ qdio_req; int /*<<< orphan*/  issued; int /*<<< orphan*/ * qtcb; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  req_no; int /*<<< orphan*/  fsf_req_seq_no; int /*<<< orphan*/  req_list; struct zfcp_qdio* qdio; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tod_clock () ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zfcp_qdio_send (struct zfcp_qdio*,TYPE_1__*) ; 
 int /*<<< orphan*/  zfcp_reqlist_add (int /*<<< orphan*/ ,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_reqlist_find_rm (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zfcp_fsf_req_send(struct zfcp_fsf_req *req)
{
	struct zfcp_adapter *adapter = req->adapter;
	struct zfcp_qdio *qdio = adapter->qdio;
	int with_qtcb = (req->qtcb != NULL);
	int req_id = req->req_id;

	zfcp_reqlist_add(adapter->req_list, req);

	req->qdio_req.qdio_outb_usage = atomic_read(&qdio->req_q_free);
	req->issued = get_tod_clock();
	if (zfcp_qdio_send(qdio, &req->qdio_req)) {
		del_timer(&req->timer);
		/* lookup request again, list might have changed */
		zfcp_reqlist_find_rm(adapter->req_list, req_id);
		zfcp_erp_adapter_reopen(adapter, 0, "fsrs__1");
		return -EIO;
	}

	/* Don't increase for unsolicited status */
	if (with_qtcb)
		adapter->fsf_req_seq_no++;
	adapter->req_no++;

	return 0;
}