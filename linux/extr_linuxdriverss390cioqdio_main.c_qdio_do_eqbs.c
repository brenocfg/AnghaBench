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
struct qdio_q {int nr; TYPE_1__* irq_ptr; int /*<<< orphan*/  first_to_kick; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  is_input_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_parm; int /*<<< orphan*/  cdev; int /*<<< orphan*/  sch_token; scalar_t__ nr_input_qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,TYPE_1__*,char*,unsigned int) ; 
 int /*<<< orphan*/  DBF_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  DBF_WARN ; 
 int /*<<< orphan*/  QDIO_ERROR_GET_BUF_STATE ; 
 int /*<<< orphan*/  SCH_NO (struct qdio_q*) ; 
 unsigned int do_eqbs (int /*<<< orphan*/ ,unsigned char*,int,int*,int*,int) ; 
 int /*<<< orphan*/  eqbs ; 
 int /*<<< orphan*/  eqbs_partial ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qdio_do_eqbs(struct qdio_q *q, unsigned char *state,
			int start, int count, int auto_ack)
{
	int tmp_count = count, tmp_start = start, nr = q->nr;
	unsigned int ccq = 0;

	qperf_inc(q, eqbs);

	if (!q->is_input_q)
		nr += q->irq_ptr->nr_input_qs;
again:
	ccq = do_eqbs(q->irq_ptr->sch_token, state, nr, &tmp_start, &tmp_count,
		      auto_ack);

	switch (ccq) {
	case 0:
	case 32:
		/* all done, or next buffer state different */
		return count - tmp_count;
	case 96:
		/* not all buffers processed */
		qperf_inc(q, eqbs_partial);
		DBF_DEV_EVENT(DBF_WARN, q->irq_ptr, "EQBS part:%02x",
			tmp_count);
		return count - tmp_count;
	case 97:
		/* no buffer processed */
		DBF_DEV_EVENT(DBF_WARN, q->irq_ptr, "EQBS again:%2d", ccq);
		goto again;
	default:
		DBF_ERROR("%4x ccq:%3d", SCH_NO(q), ccq);
		DBF_ERROR("%4x EQBS ERROR", SCH_NO(q));
		DBF_ERROR("%3d%3d%2d", count, tmp_count, nr);
		q->handler(q->irq_ptr->cdev, QDIO_ERROR_GET_BUF_STATE, q->nr,
			   q->first_to_kick, count, q->irq_ptr->int_parm);
		return 0;
	}
}