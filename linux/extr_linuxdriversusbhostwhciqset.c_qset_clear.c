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
struct TYPE_2__ {int status; int /*<<< orphan*/  overlay; scalar_t__* scratch; scalar_t__ err_count; int /*<<< orphan*/  link; } ;
struct whc_qset {int /*<<< orphan*/  remove_complete; TYPE_1__ qh; scalar_t__ ntds; scalar_t__ td_end; scalar_t__ td_start; } ;
struct whc {int dummy; } ;

/* Variables and functions */
 int QH_LINK_NTDS (int) ; 
 int QH_LINK_T ; 
 int QH_STATUS_SEQ_MASK ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void qset_clear(struct whc *whc, struct whc_qset *qset)
{
	qset->td_start = qset->td_end = qset->ntds = 0;

	qset->qh.link = cpu_to_le64(QH_LINK_NTDS(8) | QH_LINK_T);
	qset->qh.status = qset->qh.status & QH_STATUS_SEQ_MASK;
	qset->qh.err_count = 0;
	qset->qh.scratch[0] = 0;
	qset->qh.scratch[1] = 0;
	qset->qh.scratch[2] = 0;

	memset(&qset->qh.overlay, 0, sizeof(qset->qh.overlay));

	init_completion(&qset->remove_complete);
}