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
struct vnt_private {scalar_t__ free_cmd_queue; int cmd_running; int command; int* cmd_queue; size_t cmd_dequeue_idx; int /*<<< orphan*/  command_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_ONE_WITH_WRAP_AROUND (size_t,scalar_t__) ; 
 scalar_t__ CMD_Q_SIZE ; 
#define  WLAN_CMD_BECON_SEND 132 
 int /*<<< orphan*/  WLAN_CMD_BECON_SEND_START ; 
#define  WLAN_CMD_CHANGE_ANTENNA 131 
 int /*<<< orphan*/  WLAN_CMD_CHANGE_ANTENNA_START ; 
 int /*<<< orphan*/  WLAN_CMD_IDLE ; 
#define  WLAN_CMD_INIT_MAC80211 130 
 int /*<<< orphan*/  WLAN_CMD_INIT_MAC80211_START ; 
#define  WLAN_CMD_SETPOWER 129 
 int /*<<< orphan*/  WLAN_CMD_SETPOWER_START ; 
#define  WLAN_CMD_TBTT_WAKEUP 128 
 int /*<<< orphan*/  WLAN_CMD_TBTT_WAKEUP_START ; 
 int /*<<< orphan*/  vnt_cmd_timer_wait (struct vnt_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vnt_cmd_complete(struct vnt_private *priv)
{
	priv->command_state = WLAN_CMD_IDLE;
	if (priv->free_cmd_queue == CMD_Q_SIZE) {
		/* Command Queue Empty */
		priv->cmd_running = false;
		return true;
	}

	priv->command = priv->cmd_queue[priv->cmd_dequeue_idx];

	ADD_ONE_WITH_WRAP_AROUND(priv->cmd_dequeue_idx, CMD_Q_SIZE);
	priv->free_cmd_queue++;
	priv->cmd_running = true;

	switch (priv->command) {
	case WLAN_CMD_INIT_MAC80211:
		priv->command_state = WLAN_CMD_INIT_MAC80211_START;
		break;

	case WLAN_CMD_TBTT_WAKEUP:
		priv->command_state = WLAN_CMD_TBTT_WAKEUP_START;
		break;

	case WLAN_CMD_BECON_SEND:
		priv->command_state = WLAN_CMD_BECON_SEND_START;
		break;

	case WLAN_CMD_SETPOWER:
		priv->command_state = WLAN_CMD_SETPOWER_START;
		break;

	case WLAN_CMD_CHANGE_ANTENNA:
		priv->command_state = WLAN_CMD_CHANGE_ANTENNA_START;
		break;

	default:
		break;
	}

	vnt_cmd_timer_wait(priv, 0);

	return true;
}