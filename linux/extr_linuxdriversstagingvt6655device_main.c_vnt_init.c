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
struct vnt_private {int mac_hw; int /*<<< orphan*/  hw; int /*<<< orphan*/  abyCurrentNetAddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARDbRadioPowerOff (struct vnt_private*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_register_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_init_bands (struct vnt_private*) ; 

__attribute__((used)) static int vnt_init(struct vnt_private *priv)
{
	SET_IEEE80211_PERM_ADDR(priv->hw, priv->abyCurrentNetAddr);

	vnt_init_bands(priv);

	if (ieee80211_register_hw(priv->hw))
		return -ENODEV;

	priv->mac_hw = true;

	CARDbRadioPowerOff(priv);

	return 0;
}