#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct at76_priv {int radio_on; TYPE_1__* hw; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int CMD_RADIO_OFF ; 
 int CMD_RADIO_ON ; 
 int at76_set_card_command (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int at76_set_radio(struct at76_priv *priv, int enable)
{
	int ret;
	int cmd;

	if (priv->radio_on == enable)
		return 0;

	cmd = enable ? CMD_RADIO_ON : CMD_RADIO_OFF;

	ret = at76_set_card_command(priv->udev, cmd, NULL, 0);
	if (ret < 0)
		wiphy_err(priv->hw->wiphy,
			  "at76_set_card_command(%d) failed: %d\n", cmd, ret);
	else
		ret = 1;

	priv->radio_on = enable;
	return ret;
}