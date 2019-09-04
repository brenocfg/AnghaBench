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
struct ks_wlan_private {scalar_t__ version_size; scalar_t__ dev_state; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  confirm_wait; scalar_t__ mac_address_valid; } ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_PREINIT ; 
 scalar_t__ DEVICE_STATE_READY ; 
 int HZ ; 
 int /*<<< orphan*/  SME_START ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ks7010_sme_enqueue_events (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ks7010_card_init(struct ks_wlan_private *priv)
{
	init_completion(&priv->confirm_wait);

	/* get mac address & firmware version */
	hostif_sme_enqueue(priv, SME_START);

	if (!wait_for_completion_interruptible_timeout
	    (&priv->confirm_wait, 5 * HZ)) {
		netdev_dbg(priv->net_dev, "wait time out!! SME_START\n");
	}

	if (priv->mac_address_valid && priv->version_size != 0)
		priv->dev_state = DEVICE_STATE_PREINIT;

	ks7010_sme_enqueue_events(priv);

	if (!wait_for_completion_interruptible_timeout
	    (&priv->confirm_wait, 5 * HZ)) {
		netdev_dbg(priv->net_dev, "wait time out!! wireless parameter set\n");
	}

	if (priv->dev_state >= DEVICE_STATE_PREINIT) {
		netdev_dbg(priv->net_dev, "DEVICE READY!!\n");
		priv->dev_state = DEVICE_STATE_READY;
	}
}