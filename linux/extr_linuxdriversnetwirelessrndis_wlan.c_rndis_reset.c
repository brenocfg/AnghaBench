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
struct usbnet {int dummy; } ;
struct rndis_wlan_private {int /*<<< orphan*/  command_lock; scalar_t__ current_command_oid; scalar_t__ command_buffer; } ;
struct rndis_reset {void* msg_len; void* msg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_BUFFER_SIZE ; 
 int RNDIS_MSG_RESET ; 
 void* cpu_to_le32 (int) ; 
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 
 int /*<<< orphan*/  memset (struct rndis_reset*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rndis_command (struct usbnet*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rndis_reset(struct usbnet *usbdev)
{
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);
	struct rndis_reset *reset;
	int ret;

	mutex_lock(&priv->command_lock);

	reset = (void *)priv->command_buffer;
	memset(reset, 0, sizeof(*reset));
	reset->msg_type = cpu_to_le32(RNDIS_MSG_RESET);
	reset->msg_len = cpu_to_le32(sizeof(*reset));
	priv->current_command_oid = 0;
	ret = rndis_command(usbdev, (void *)reset, CONTROL_BUFFER_SIZE);

	mutex_unlock(&priv->command_lock);

	if (ret < 0)
		return ret;
	return 0;
}