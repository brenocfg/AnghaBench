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
struct TYPE_3__ {scalar_t__ ack_count; int ack_start; scalar_t__ polling; } ;
struct TYPE_4__ {TYPE_1__ in; } ;
struct qdio_q {int /*<<< orphan*/  nr_buf_used; TYPE_2__ u; } ;

/* Variables and functions */
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  SLSB_CU_INPUT_EMPTY ; 
 void* add_buf (int,int) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ buf_in_between (int,int,int) ; 
 int /*<<< orphan*/  inbound_call ; 
 scalar_t__ is_qebsm (struct qdio_q*) ; 
 scalar_t__ need_siga_in (struct qdio_q*) ; 
 int qdio_siga_input (struct qdio_q*) ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 
 int set_buf_states (struct qdio_q*,int,int /*<<< orphan*/ ,int) ; 
 int sub_buf (int,int) ; 

__attribute__((used)) static int handle_inbound(struct qdio_q *q, unsigned int callflags,
			  int bufnr, int count)
{
	int diff;

	qperf_inc(q, inbound_call);

	if (!q->u.in.polling)
		goto set;

	/* protect against stop polling setting an ACK for an emptied slsb */
	if (count == QDIO_MAX_BUFFERS_PER_Q) {
		/* overwriting everything, just delete polling status */
		q->u.in.polling = 0;
		q->u.in.ack_count = 0;
		goto set;
	} else if (buf_in_between(q->u.in.ack_start, bufnr, count)) {
		if (is_qebsm(q)) {
			/* partial overwrite, just update ack_start */
			diff = add_buf(bufnr, count);
			diff = sub_buf(diff, q->u.in.ack_start);
			q->u.in.ack_count -= diff;
			if (q->u.in.ack_count <= 0) {
				q->u.in.polling = 0;
				q->u.in.ack_count = 0;
				goto set;
			}
			q->u.in.ack_start = add_buf(q->u.in.ack_start, diff);
		}
		else
			/* the only ACK will be deleted, so stop polling */
			q->u.in.polling = 0;
	}

set:
	count = set_buf_states(q, bufnr, SLSB_CU_INPUT_EMPTY, count);
	atomic_add(count, &q->nr_buf_used);

	if (need_siga_in(q))
		return qdio_siga_input(q);

	return 0;
}