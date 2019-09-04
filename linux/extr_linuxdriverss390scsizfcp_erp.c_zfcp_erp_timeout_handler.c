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
struct zfcp_fsf_req {struct zfcp_erp_action* erp_action; } ;
struct zfcp_erp_action {int dummy; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_ERP_TIMEDOUT ; 
 struct zfcp_fsf_req* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct zfcp_fsf_req* fsf_req ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  zfcp_erp_notify (struct zfcp_erp_action*,int /*<<< orphan*/ ) ; 

void zfcp_erp_timeout_handler(struct timer_list *t)
{
	struct zfcp_fsf_req *fsf_req = from_timer(fsf_req, t, timer);
	struct zfcp_erp_action *act = fsf_req->erp_action;

	zfcp_erp_notify(act, ZFCP_STATUS_ERP_TIMEDOUT);
}