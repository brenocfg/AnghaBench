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
struct efx_nic {int mc_bist_for_other_fn; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int BIST_WAIT_DELAY_COUNT ; 
 int /*<<< orphan*/  BIST_WAIT_DELAY_MS ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ efx_mcdi_poll_reboot (struct efx_nic*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void efx_wait_for_bist_end(struct efx_nic *efx)
{
	int i;

	for (i = 0; i < BIST_WAIT_DELAY_COUNT; ++i) {
		if (efx_mcdi_poll_reboot(efx))
			goto out;
		msleep(BIST_WAIT_DELAY_MS);
	}

	netif_err(efx, drv, efx->net_dev, "Warning: No MC reboot after BIST mode\n");
out:
	/* Either way unset the BIST flag. If we found no reboot we probably
	 * won't recover, but we should try.
	 */
	efx->mc_bist_for_other_fn = false;
}