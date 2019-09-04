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
typedef  int u32 ;
struct usb3phy_reg {int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  offset; } ;
struct rockchip_usb3phy_port_cfg {struct usb3phy_reg pipe_status; } ;
struct rockchip_typec_phy {int mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  grf_regs; struct rockchip_usb3phy_port_cfg* port_cfgs; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int MODE_DFP_USB ; 
 int MODE_DISCONNECT ; 
 int MODE_UFP_USB ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rockchip_typec_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tcphy_cfg_usb3_to_usb2_only (struct rockchip_typec_phy*,int) ; 
 int tcphy_get_mode (struct rockchip_typec_phy*) ; 
 int /*<<< orphan*/  tcphy_phy_deinit (struct rockchip_typec_phy*) ; 
 int tcphy_phy_init (struct rockchip_typec_phy*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rockchip_usb3_phy_power_on(struct phy *phy)
{
	struct rockchip_typec_phy *tcphy = phy_get_drvdata(phy);
	const struct rockchip_usb3phy_port_cfg *cfg = tcphy->port_cfgs;
	const struct usb3phy_reg *reg = &cfg->pipe_status;
	int timeout, new_mode, ret = 0;
	u32 val;

	mutex_lock(&tcphy->lock);

	new_mode = tcphy_get_mode(tcphy);
	if (new_mode < 0) {
		ret = new_mode;
		goto unlock_ret;
	}

	/* DP-only mode; fall back to USB2 */
	if (!(new_mode & (MODE_DFP_USB | MODE_UFP_USB))) {
		tcphy_cfg_usb3_to_usb2_only(tcphy, true);
		goto unlock_ret;
	}

	if (tcphy->mode == new_mode)
		goto unlock_ret;

	if (tcphy->mode == MODE_DISCONNECT) {
		ret = tcphy_phy_init(tcphy, new_mode);
		if (ret)
			goto unlock_ret;
	}

	/* wait TCPHY for pipe ready */
	for (timeout = 0; timeout < 100; timeout++) {
		regmap_read(tcphy->grf_regs, reg->offset, &val);
		if (!(val & BIT(reg->enable_bit))) {
			tcphy->mode |= new_mode & (MODE_DFP_USB | MODE_UFP_USB);

			/* enable usb3 host */
			tcphy_cfg_usb3_to_usb2_only(tcphy, false);
			goto unlock_ret;
		}
		usleep_range(10, 20);
	}

	if (tcphy->mode == MODE_DISCONNECT)
		tcphy_phy_deinit(tcphy);

	ret = -ETIMEDOUT;

unlock_ret:
	mutex_unlock(&tcphy->lock);
	return ret;
}