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
struct fc_fcp_pkt {int /*<<< orphan*/  seq_ptr; int /*<<< orphan*/  state; TYPE_1__* lp; } ;
struct TYPE_4__ {int /*<<< orphan*/  FcpPktAborts; } ;
struct TYPE_3__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  FC_SRB_ABORT_PENDING ; 
 int /*<<< orphan*/  fc_fcp_abort_done (struct fc_fcp_pkt*) ; 
 int fc_seq_exch_abort (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cpu () ; 
 TYPE_2__* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cpu () ; 

__attribute__((used)) static int fc_fcp_send_abort(struct fc_fcp_pkt *fsp)
{
	int rc;

	if (!fsp->seq_ptr)
		return -EINVAL;

	per_cpu_ptr(fsp->lp->stats, get_cpu())->FcpPktAborts++;
	put_cpu();

	fsp->state |= FC_SRB_ABORT_PENDING;
	rc = fc_seq_exch_abort(fsp->seq_ptr, 0);
	/*
	 * fc_seq_exch_abort() might return -ENXIO if
	 * the sequence is already completed
	 */
	if (rc == -ENXIO) {
		fc_fcp_abort_done(fsp);
		rc = 0;
	}
	return rc;
}