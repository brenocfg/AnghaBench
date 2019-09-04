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
struct bmi_xfer {int tx_done; } ;
struct ath10k_ce_pipe {int dummy; } ;

/* Variables and functions */
 scalar_t__ ath10k_ce_completed_send_next (struct ath10k_ce_pipe*,void**) ; 

__attribute__((used)) static void ath10k_pci_bmi_send_done(struct ath10k_ce_pipe *ce_state)
{
	struct bmi_xfer *xfer;

	if (ath10k_ce_completed_send_next(ce_state, (void **)&xfer))
		return;

	xfer->tx_done = true;
}