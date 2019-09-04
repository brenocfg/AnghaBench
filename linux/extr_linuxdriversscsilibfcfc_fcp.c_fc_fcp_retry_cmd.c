#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fc_fcp_pkt {int status_code; scalar_t__ io_status; int /*<<< orphan*/  state; int /*<<< orphan*/ * seq_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_SRB_ABORT_PENDING ; 
 int /*<<< orphan*/  fc_exch_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_fcp_complete_locked (struct fc_fcp_pkt*) ; 

__attribute__((used)) static void fc_fcp_retry_cmd(struct fc_fcp_pkt *fsp, int status_code)
{
	if (fsp->seq_ptr) {
		fc_exch_done(fsp->seq_ptr);
		fsp->seq_ptr = NULL;
	}

	fsp->state &= ~FC_SRB_ABORT_PENDING;
	fsp->io_status = 0;
	fsp->status_code = status_code;
	fc_fcp_complete_locked(fsp);
}