#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct esas2r_request {int /*<<< orphan*/  comp_list; int /*<<< orphan*/  func_rsp; TYPE_3__* vrq; struct esas2r_request* req_stat; int /*<<< orphan*/  req_list; } ;
struct TYPE_4__ {scalar_t__ virt_addr; } ;
struct esas2r_adapter {int last_read; int list_size; int /*<<< orphan*/  queue_lock; struct esas2r_request** req_table; TYPE_1__ outbound_list_md; int /*<<< orphan*/ * outbound_copy; } ;
struct atto_vda_ob_rsp {int handle; int /*<<< orphan*/  func_rsp; struct esas2r_request* req_stat; } ;
struct TYPE_5__ {int handle; scalar_t__ function; } ;
struct TYPE_6__ {TYPE_2__ scsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 size_t LOWORD (int) ; 
 int MU_OLC_WRT_PTR ; 
 scalar_t__ VDA_FUNC_SCSI ; 
 int /*<<< orphan*/  comp_list ; 
 int /*<<< orphan*/  esas2r_bugon () ; 
 int /*<<< orphan*/  esas2r_comp_list_drain (struct esas2r_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_handle_outbound_rsp_err (struct esas2r_adapter*,struct esas2r_request*,struct atto_vda_ob_rsp*) ; 
 int /*<<< orphan*/  esas2r_local_reset_adapter (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_trace (char*,...) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t num_ae_requests ; 
 size_t num_requests ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void esas2r_get_outbound_responses(struct esas2r_adapter *a)
{
	struct atto_vda_ob_rsp *rsp;
	u32 rspput_ptr;
	u32 rspget_ptr;
	struct esas2r_request *rq;
	u32 handle;
	unsigned long flags;

	LIST_HEAD(comp_list);

	esas2r_trace_enter();

	spin_lock_irqsave(&a->queue_lock, flags);

	/* Get the outbound limit and pointers */
	rspput_ptr = le32_to_cpu(*a->outbound_copy) & MU_OLC_WRT_PTR;
	rspget_ptr = a->last_read;

	esas2r_trace("rspput_ptr: %x, rspget_ptr: %x", rspput_ptr, rspget_ptr);

	/* If we don't have anything to process, get out */
	if (unlikely(rspget_ptr == rspput_ptr)) {
		spin_unlock_irqrestore(&a->queue_lock, flags);
		esas2r_trace_exit();
		return;
	}

	/* Make sure the firmware is healthy */
	if (unlikely(rspput_ptr >= a->list_size)) {
		spin_unlock_irqrestore(&a->queue_lock, flags);
		esas2r_bugon();
		esas2r_local_reset_adapter(a);
		esas2r_trace_exit();
		return;
	}

	do {
		rspget_ptr++;

		if (rspget_ptr >= a->list_size)
			rspget_ptr = 0;

		rsp = (struct atto_vda_ob_rsp *)a->outbound_list_md.virt_addr
		      + rspget_ptr;

		handle = rsp->handle;

		/* Verify the handle range */
		if (unlikely(LOWORD(handle) == 0
			     || LOWORD(handle) > num_requests +
			     num_ae_requests + 1)) {
			esas2r_bugon();
			continue;
		}

		/* Get the request for this handle */
		rq = a->req_table[LOWORD(handle)];

		if (unlikely(rq == NULL || rq->vrq->scsi.handle != handle)) {
			esas2r_bugon();
			continue;
		}

		list_del(&rq->req_list);

		/* Get the completion status */
		rq->req_stat = rsp->req_stat;

		esas2r_trace("handle: %x", handle);
		esas2r_trace("rq: %p", rq);
		esas2r_trace("req_status: %x", rq->req_stat);

		if (likely(rq->vrq->scsi.function == VDA_FUNC_SCSI)) {
			esas2r_handle_outbound_rsp_err(a, rq, rsp);
		} else {
			/*
			 * Copy the outbound completion struct for non-I/O
			 * requests.
			 */
			memcpy(&rq->func_rsp, &rsp->func_rsp,
			       sizeof(rsp->func_rsp));
		}

		/* Queue the request for completion. */
		list_add_tail(&rq->comp_list, &comp_list);

	} while (rspget_ptr != rspput_ptr);

	a->last_read = rspget_ptr;
	spin_unlock_irqrestore(&a->queue_lock, flags);

	esas2r_comp_list_drain(a, &comp_list);
	esas2r_trace_exit();
}