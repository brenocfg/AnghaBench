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
struct esas2r_sas_nvram {int dummy; } ;
struct esas2r_request {scalar_t__ req_stat; int /*<<< orphan*/  comp_cb; } ;
struct esas2r_adapter {scalar_t__ nvram_command_done; int /*<<< orphan*/  nvram_waiter; } ;

/* Variables and functions */
 scalar_t__ RS_SUCCESS ; 
 int /*<<< orphan*/  complete_nvr_req ; 
 scalar_t__ esas2r_nvram_write (struct esas2r_adapter*,struct esas2r_request*,struct esas2r_sas_nvram*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 

int esas2r_write_params(struct esas2r_adapter *a, struct esas2r_request *rq,
			struct esas2r_sas_nvram *data)
{
	int result = 0;

	a->nvram_command_done = 0;
	rq->comp_cb = complete_nvr_req;

	if (esas2r_nvram_write(a, rq, data)) {
		/* now wait around for it to complete. */
		while (!a->nvram_command_done)
			wait_event_interruptible(a->nvram_waiter,
						 a->nvram_command_done);
		;

		/* done, check the status. */
		if (rq->req_stat == RS_SUCCESS)
			result = 1;
	}
	return result;
}