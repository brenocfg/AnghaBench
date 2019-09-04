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
struct vnt_private {int cmd_running; int /*<<< orphan*/  interrupt_urb; int /*<<< orphan*/  run_command_work; int /*<<< orphan*/  flags; scalar_t__ key_entry_inuse; } ;
struct ieee80211_hw {struct vnt_private* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_FLAGS_DISCONNECTED ; 
 int /*<<< orphan*/  DEVICE_FLAGS_UNPLUG ; 
 int MAX_KEY_TABLE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_free_int_bufs (struct vnt_private*) ; 
 int /*<<< orphan*/  vnt_free_rx_bufs (struct vnt_private*) ; 
 int /*<<< orphan*/  vnt_free_tx_bufs (struct vnt_private*) ; 
 int /*<<< orphan*/  vnt_mac_disable_keyentry (struct vnt_private*,int) ; 
 int /*<<< orphan*/  vnt_mac_shutdown (struct vnt_private*) ; 

__attribute__((used)) static void vnt_stop(struct ieee80211_hw *hw)
{
	struct vnt_private *priv = hw->priv;
	int i;

	if (!priv)
		return;

	for (i = 0; i < MAX_KEY_TABLE; i++)
		vnt_mac_disable_keyentry(priv, i);

	/* clear all keys */
	priv->key_entry_inuse = 0;

	if (!test_bit(DEVICE_FLAGS_UNPLUG, &priv->flags))
		vnt_mac_shutdown(priv);

	ieee80211_stop_queues(hw);

	set_bit(DEVICE_FLAGS_DISCONNECTED, &priv->flags);

	cancel_delayed_work_sync(&priv->run_command_work);

	priv->cmd_running = false;

	vnt_free_tx_bufs(priv);
	vnt_free_rx_bufs(priv);
	vnt_free_int_bufs(priv);

	usb_kill_urb(priv->interrupt_urb);
	usb_free_urb(priv->interrupt_urb);
}