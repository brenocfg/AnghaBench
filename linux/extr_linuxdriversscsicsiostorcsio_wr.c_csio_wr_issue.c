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
struct csio_wrm {int free_qidx; struct csio_q** q_arr; } ;
struct TYPE_3__ {int /*<<< orphan*/  physeqid; } ;
struct TYPE_4__ {TYPE_1__ eq; } ;
struct csio_q {scalar_t__ inc_idx; TYPE_2__ un; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int) ; 
 int DBPRIO_V (int) ; 
 int DBTYPE_F ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int PIDX_T5_V (scalar_t__) ; 
 int QID_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGE_PF_KDOORBELL_A ; 
 struct csio_wrm* csio_hw_to_wrm (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

int
csio_wr_issue(struct csio_hw *hw, int qidx, bool prio)
{
	struct csio_wrm *wrm = csio_hw_to_wrm(hw);
	struct csio_q *q = wrm->q_arr[qidx];

	CSIO_DB_ASSERT((qidx >= 0) && (qidx < wrm->free_qidx));

	wmb();
	/* Ring SGE Doorbell writing q->pidx into it */
	csio_wr_reg32(hw, DBPRIO_V(prio) | QID_V(q->un.eq.physeqid) |
			  PIDX_T5_V(q->inc_idx) | DBTYPE_F,
			  MYPF_REG(SGE_PF_KDOORBELL_A));
	q->inc_idx = 0;

	return 0;
}