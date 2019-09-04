#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct rndis_query_complete {scalar_t__ status; int info_buflen; scalar_t__ info_buf_offset; } ;
struct TYPE_3__ {struct rndis_query_complete query_complete; } ;
struct TYPE_4__ {TYPE_1__ msg; } ;
struct rndis_request {TYPE_2__ response_msg; } ;
struct rndis_device {int link_state; } ;

/* Variables and functions */
 scalar_t__ RNDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,void*,int) ; 

__attribute__((used)) static void rndis_set_link_state(struct rndis_device *rdev,
				 struct rndis_request *request)
{
	u32 link_status;
	struct rndis_query_complete *query_complete;

	query_complete = &request->response_msg.msg.query_complete;

	if (query_complete->status == RNDIS_STATUS_SUCCESS &&
	    query_complete->info_buflen == sizeof(u32)) {
		memcpy(&link_status, (void *)((unsigned long)query_complete +
		       query_complete->info_buf_offset), sizeof(u32));
		rdev->link_state = link_status != 0;
	}
}