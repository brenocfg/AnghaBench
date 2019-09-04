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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct sbp_management_request {TYPE_1__ status; } ;
struct sbp_management_agent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBP_STATUS_REQ_TYPE_NOTSUPP ; 
 int STATUS_BLOCK_RESP (int /*<<< orphan*/ ) ; 
 int STATUS_BLOCK_SBP_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_RESP_REQUEST_COMPLETE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 

__attribute__((used)) static void sbp_management_request_query_logins(
	struct sbp_management_agent *agent, struct sbp_management_request *req,
	int *status_data_size)
{
	pr_notice("QUERY LOGINS not implemented\n");
	/* FIXME: implement */

	req->status.status = cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_REQ_TYPE_NOTSUPP));
}