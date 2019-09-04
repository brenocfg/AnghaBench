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
struct vnt_private {int mac_hw; int /*<<< orphan*/  hw; int /*<<< orphan*/  permanent_net_addr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_register_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_init_bands (struct vnt_private*) ; 
 int /*<<< orphan*/  vnt_init_registers (struct vnt_private*) ; 
 int /*<<< orphan*/  vnt_radio_power_off (struct vnt_private*) ; 

int vnt_init(struct vnt_private *priv)
{
	if (!(vnt_init_registers(priv)))
		return -EAGAIN;

	SET_IEEE80211_PERM_ADDR(priv->hw, priv->permanent_net_addr);

	vnt_init_bands(priv);

	if (ieee80211_register_hw(priv->hw))
		return -ENODEV;

	priv->mac_hw = true;

	vnt_radio_power_off(priv);

	return 0;
}