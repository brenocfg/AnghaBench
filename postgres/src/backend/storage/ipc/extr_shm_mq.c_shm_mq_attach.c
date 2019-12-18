#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mqh_length_word_complete; int mqh_counterparty_attached; int /*<<< orphan*/  mqh_context; scalar_t__ mqh_expected_bytes; scalar_t__ mqh_partial_bytes; scalar_t__ mqh_consume_pending; scalar_t__ mqh_buflen; int /*<<< orphan*/ * mqh_buffer; int /*<<< orphan*/ * mqh_handle; int /*<<< orphan*/ * mqh_segment; TYPE_2__* mqh_queue; } ;
typedef  TYPE_1__ shm_mq_handle ;
struct TYPE_8__ {scalar_t__ mq_receiver; scalar_t__ mq_sender; } ;
typedef  TYPE_2__ shm_mq ;
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ MyProc ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_2__*) ; 
 int /*<<< orphan*/  on_dsm_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  shm_mq_detach_callback ; 

shm_mq_handle *
shm_mq_attach(shm_mq *mq, dsm_segment *seg, BackgroundWorkerHandle *handle)
{
	shm_mq_handle *mqh = palloc(sizeof(shm_mq_handle));

	Assert(mq->mq_receiver == MyProc || mq->mq_sender == MyProc);
	mqh->mqh_queue = mq;
	mqh->mqh_segment = seg;
	mqh->mqh_handle = handle;
	mqh->mqh_buffer = NULL;
	mqh->mqh_buflen = 0;
	mqh->mqh_consume_pending = 0;
	mqh->mqh_partial_bytes = 0;
	mqh->mqh_expected_bytes = 0;
	mqh->mqh_length_word_complete = false;
	mqh->mqh_counterparty_attached = false;
	mqh->mqh_context = CurrentMemoryContext;

	if (seg != NULL)
		on_dsm_detach(seg, shm_mq_detach_callback, PointerGetDatum(mq));

	return mqh;
}