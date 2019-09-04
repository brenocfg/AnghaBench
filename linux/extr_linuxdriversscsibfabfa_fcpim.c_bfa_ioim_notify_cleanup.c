#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfa_ioim_s {TYPE_3__* iosp; TYPE_4__* itnim; int /*<<< orphan*/  qe; int /*<<< orphan*/  hcb_qe; TYPE_1__* fcpim; } ;
struct TYPE_8__ {int /*<<< orphan*/  delay_comp_q; scalar_t__ iotov_active; } ;
struct TYPE_7__ {TYPE_2__* tskim; } ;
struct TYPE_6__ {int /*<<< orphan*/  wc; } ;
struct TYPE_5__ {scalar_t__ delay_comp; int /*<<< orphan*/  ioim_comp_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_cb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_itnim_iodone (TYPE_4__*) ; 
 int /*<<< orphan*/  bfa_wc_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_ioim_notify_cleanup(struct bfa_ioim_s *ioim)
{
	/*
	 * Move IO from itnim queue to fcpim global queue since itnim will be
	 * freed.
	 */
	list_del(&ioim->qe);
	list_add_tail(&ioim->qe, &ioim->fcpim->ioim_comp_q);

	if (!ioim->iosp->tskim) {
		if (ioim->fcpim->delay_comp && ioim->itnim->iotov_active) {
			bfa_cb_dequeue(&ioim->hcb_qe);
			list_del(&ioim->qe);
			list_add_tail(&ioim->qe, &ioim->itnim->delay_comp_q);
		}
		bfa_itnim_iodone(ioim->itnim);
	} else
		bfa_wc_down(&ioim->iosp->tskim->wc);
}