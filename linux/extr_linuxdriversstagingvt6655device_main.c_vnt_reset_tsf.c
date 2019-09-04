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
struct vnt_private {scalar_t__ PortOffset; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct vnt_private* priv; } ;

/* Variables and functions */
 scalar_t__ MAC_REG_TFTCTL ; 
 int /*<<< orphan*/  TFTCTL_TSFCNTRST ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vnt_reset_tsf(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct vnt_private *priv = hw->priv;

	/* reset TSF counter */
	VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL, TFTCTL_TSFCNTRST);
}