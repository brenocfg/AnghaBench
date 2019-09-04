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
struct smsc911x_data {int /*<<< orphan*/  mac_lock; scalar_t__ multicast_update_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CR ; 
 int MAC_CR_RXEN_ ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drv ; 
 int smsc911x_mac_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_mac_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  smsc911x_rx_multicast_update (struct smsc911x_data*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smsc911x_rx_multicast_update_workaround(struct smsc911x_data *pdata)
{
	unsigned int mac_cr;

	/* This function is only called for older LAN911x devices
	 * (revA or revB), where MAC_CR, HASHH and HASHL should not
	 * be modified during Rx - newer devices immediately update the
	 * registers.
	 *
	 * This is called from interrupt context */

	spin_lock(&pdata->mac_lock);

	/* Check Rx has stopped */
	if (smsc911x_mac_read(pdata, MAC_CR) & MAC_CR_RXEN_)
		SMSC_WARN(pdata, drv, "Rx not stopped");

	/* Perform the update - safe to do now Rx has stopped */
	smsc911x_rx_multicast_update(pdata);

	/* Re-enable Rx */
	mac_cr = smsc911x_mac_read(pdata, MAC_CR);
	mac_cr |= MAC_CR_RXEN_;
	smsc911x_mac_write(pdata, MAC_CR, mac_cr);

	pdata->multicast_update_pending = 0;

	spin_unlock(&pdata->mac_lock);
}