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
struct esas2r_request {scalar_t__ req_stat; } ;
struct esas2r_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_DEGRADED_MODE ; 
 scalar_t__ RS_PENDING ; 
 int /*<<< orphan*/  build_flash_msg (struct esas2r_adapter*,struct esas2r_request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool load_image(struct esas2r_adapter *a, struct esas2r_request *rq)
{
	/*
	 * assume we have more to do.  if we return with the status set to
	 * RS_PENDING, FM API tasks will continue.
	 */
	rq->req_stat = RS_PENDING;
	if (test_bit(AF_DEGRADED_MODE, &a->flags))
		/* not suppported for now */;
	else
		build_flash_msg(a, rq);

	return rq->req_stat == RS_PENDING;
}