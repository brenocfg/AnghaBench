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
struct vnt_private {int cmd_running; int /*<<< orphan*/  command_state; scalar_t__ cmd_enqueue_idx; scalar_t__ cmd_dequeue_idx; int /*<<< orphan*/  free_cmd_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_Q_SIZE ; 
 int /*<<< orphan*/  WLAN_CMD_IDLE ; 

void vnt_reset_command_timer(struct vnt_private *priv)
{
	priv->free_cmd_queue = CMD_Q_SIZE;
	priv->cmd_dequeue_idx = 0;
	priv->cmd_enqueue_idx = 0;
	priv->command_state = WLAN_CMD_IDLE;
	priv->cmd_running = false;
}