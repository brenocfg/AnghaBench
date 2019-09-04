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
struct efx_nic {int dummy; } ;
struct efx_mcdi_iface {int resprc; int /*<<< orphan*/  iface_lock; scalar_t__ resp_data_len; scalar_t__ resp_hdr_len; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long MCDI_RPC_TIMEOUT ; 
 unsigned int USER_TICK_USEC ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 scalar_t__ efx_mcdi_poll_once (struct efx_nic*) ; 
 int efx_mcdi_poll_reboot (struct efx_nic*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int efx_mcdi_poll(struct efx_nic *efx)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);
	unsigned long time, finish;
	unsigned int spins;
	int rc;

	/* Check for a reboot atomically with respect to efx_mcdi_copyout() */
	rc = efx_mcdi_poll_reboot(efx);
	if (rc) {
		spin_lock_bh(&mcdi->iface_lock);
		mcdi->resprc = rc;
		mcdi->resp_hdr_len = 0;
		mcdi->resp_data_len = 0;
		spin_unlock_bh(&mcdi->iface_lock);
		return 0;
	}

	/* Poll for completion. Poll quickly (once a us) for the 1st jiffy,
	 * because generally mcdi responses are fast. After that, back off
	 * and poll once a jiffy (approximately)
	 */
	spins = USER_TICK_USEC;
	finish = jiffies + MCDI_RPC_TIMEOUT;

	while (1) {
		if (spins != 0) {
			--spins;
			udelay(1);
		} else {
			schedule_timeout_uninterruptible(1);
		}

		time = jiffies;

		if (efx_mcdi_poll_once(efx))
			break;

		if (time_after(time, finish))
			return -ETIMEDOUT;
	}

	/* Return rc=0 like wait_event_timeout() */
	return 0;
}