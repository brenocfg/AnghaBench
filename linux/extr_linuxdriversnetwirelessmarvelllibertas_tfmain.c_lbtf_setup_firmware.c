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
struct lbtf_private {int /*<<< orphan*/  current_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBTF_DEB_FW ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbtf_set_mac_control (struct lbtf_private*) ; 
 int /*<<< orphan*/  lbtf_set_radio_control (struct lbtf_private*) ; 
 int lbtf_update_hw_spec (struct lbtf_private*) ; 

__attribute__((used)) static int lbtf_setup_firmware(struct lbtf_private *priv)
{
	int ret = -1;

	lbtf_deb_enter(LBTF_DEB_FW);
	/*
	 * Read priv address from HW
	 */
	eth_broadcast_addr(priv->current_addr);
	ret = lbtf_update_hw_spec(priv);
	if (ret) {
		ret = -1;
		goto done;
	}

	lbtf_set_mac_control(priv);
	lbtf_set_radio_control(priv);

	ret = 0;
done:
	lbtf_deb_leave_args(LBTF_DEB_FW, "ret: %d", ret);
	return ret;
}