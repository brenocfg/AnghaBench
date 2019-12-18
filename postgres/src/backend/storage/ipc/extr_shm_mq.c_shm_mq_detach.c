#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* mqh_buffer; int /*<<< orphan*/  mqh_queue; scalar_t__ mqh_segment; } ;
typedef  TYPE_1__ shm_mq_handle ;

/* Variables and functions */
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_on_dsm_detach (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  shm_mq_detach_callback ; 
 int /*<<< orphan*/  shm_mq_detach_internal (int /*<<< orphan*/ ) ; 

void
shm_mq_detach(shm_mq_handle *mqh)
{
	/* Notify counterparty that we're outta here. */
	shm_mq_detach_internal(mqh->mqh_queue);

	/* Cancel on_dsm_detach callback, if any. */
	if (mqh->mqh_segment)
		cancel_on_dsm_detach(mqh->mqh_segment,
							 shm_mq_detach_callback,
							 PointerGetDatum(mqh->mqh_queue));

	/* Release local memory associated with handle. */
	if (mqh->mqh_buffer != NULL)
		pfree(mqh->mqh_buffer);
	pfree(mqh);
}