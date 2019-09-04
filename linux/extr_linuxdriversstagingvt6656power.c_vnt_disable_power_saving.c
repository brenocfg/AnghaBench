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
struct vnt_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_REG_PSCFG ; 
 int /*<<< orphan*/  MAC_REG_PSCTL ; 
 int /*<<< orphan*/  MESSAGE_TYPE_DISABLE_PS ; 
 int /*<<< orphan*/  PSCFG_AUTOSLEEP ; 
 int /*<<< orphan*/  PSCTL_ALBCN ; 
 int /*<<< orphan*/  vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_mac_reg_bits_off (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_mac_reg_bits_on (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vnt_disable_power_saving(struct vnt_private *priv)
{
	/* disable power saving hw function */
	vnt_control_out(priv, MESSAGE_TYPE_DISABLE_PS, 0,
			0, 0, NULL);

	/* clear AutoSleep */
	vnt_mac_reg_bits_off(priv, MAC_REG_PSCFG, PSCFG_AUTOSLEEP);

	/* set always listen beacon */
	vnt_mac_reg_bits_on(priv, MAC_REG_PSCTL, PSCTL_ALBCN);
}