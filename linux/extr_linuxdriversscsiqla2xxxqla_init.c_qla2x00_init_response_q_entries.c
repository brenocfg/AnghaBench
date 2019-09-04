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
typedef  scalar_t__ uint16_t ;
struct rsp_que {scalar_t__ length; TYPE_1__* ring_ptr; int /*<<< orphan*/ * status_srb; scalar_t__ ring_index; TYPE_1__* ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  signature; } ;
typedef  TYPE_1__ response_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESPONSE_PROCESSED ; 

void
qla2x00_init_response_q_entries(struct rsp_que *rsp)
{
	uint16_t cnt;
	response_t *pkt;

	rsp->ring_ptr = rsp->ring;
	rsp->ring_index    = 0;
	rsp->status_srb = NULL;
	pkt = rsp->ring_ptr;
	for (cnt = 0; cnt < rsp->length; cnt++) {
		pkt->signature = RESPONSE_PROCESSED;
		pkt++;
	}
}