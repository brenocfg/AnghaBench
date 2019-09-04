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
struct esas2r_request {int /*<<< orphan*/  req_list; } ;
struct esas2r_adapter {int /*<<< orphan*/  active_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  esas2r_start_vda_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void esas2r_disc_local_start_request(struct esas2r_adapter *a,
				     struct esas2r_request *rq)
{
	esas2r_trace_enter();

	list_add_tail(&rq->req_list, &a->active_list);

	esas2r_start_vda_request(a, rq);

	esas2r_trace_exit();

	return;
}