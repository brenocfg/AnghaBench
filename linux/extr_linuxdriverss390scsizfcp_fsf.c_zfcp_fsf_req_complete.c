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
struct zfcp_fsf_req {scalar_t__ fsf_command; int status; int /*<<< orphan*/  completion; scalar_t__ erp_action; int /*<<< orphan*/  (* handler ) (struct zfcp_fsf_req*) ;int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ FSF_QTCB_UNSOLICITED_STATUS ; 
 int ZFCP_STATUS_FSFREQ_CLEANUP ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  stub1 (struct zfcp_fsf_req*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_erp_notify (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_fsfstatus_eval (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_protstatus_eval (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_status_read_handler (struct zfcp_fsf_req*) ; 

__attribute__((used)) static void zfcp_fsf_req_complete(struct zfcp_fsf_req *req)
{
	if (unlikely(req->fsf_command == FSF_QTCB_UNSOLICITED_STATUS)) {
		zfcp_fsf_status_read_handler(req);
		return;
	}

	del_timer(&req->timer);
	zfcp_fsf_protstatus_eval(req);
	zfcp_fsf_fsfstatus_eval(req);
	req->handler(req);

	if (req->erp_action)
		zfcp_erp_notify(req->erp_action, 0);

	if (likely(req->status & ZFCP_STATUS_FSFREQ_CLEANUP))
		zfcp_fsf_req_free(req);
	else
		complete(&req->completion);
}