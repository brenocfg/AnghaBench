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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct vnt_private {int mc_list_count; TYPE_1__* usb; } ;
struct ieee80211_hw {struct vnt_private* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_BCN_PRBRESP_PROMISC ; 
 unsigned int FIF_OTHER_BSS ; 
 int /*<<< orphan*/  MAC_REG_RCR ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_READ ; 
 int RCR_BROADCAST ; 
 int RCR_BSSID ; 
 int RCR_MULTICAST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int vnt_control_in (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  vnt_control_out_u8 (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnt_mac_set_filter (struct vnt_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vnt_configure(struct ieee80211_hw *hw,
			  unsigned int changed_flags,
			  unsigned int *total_flags, u64 multicast)
{
	struct vnt_private *priv = hw->priv;
	u8 rx_mode = 0;
	int rc;

	*total_flags &= FIF_ALLMULTI | FIF_OTHER_BSS | FIF_BCN_PRBRESP_PROMISC;

	rc = vnt_control_in(priv, MESSAGE_TYPE_READ, MAC_REG_RCR,
			    MESSAGE_REQUEST_MACREG, sizeof(u8), &rx_mode);

	if (!rc)
		rx_mode = RCR_MULTICAST | RCR_BROADCAST;

	dev_dbg(&priv->usb->dev, "rx mode in = %x\n", rx_mode);

	if (changed_flags & FIF_ALLMULTI) {
		if (*total_flags & FIF_ALLMULTI) {
			if (priv->mc_list_count > 2)
				vnt_mac_set_filter(priv, ~0);
			else
				vnt_mac_set_filter(priv, multicast);

			rx_mode |= RCR_MULTICAST | RCR_BROADCAST;
		} else {
			rx_mode &= ~(RCR_MULTICAST | RCR_BROADCAST);
		}
	}

	if (changed_flags & (FIF_OTHER_BSS | FIF_BCN_PRBRESP_PROMISC)) {
		if (*total_flags & (FIF_OTHER_BSS | FIF_BCN_PRBRESP_PROMISC))
			rx_mode &= ~RCR_BSSID;
		else
			rx_mode |= RCR_BSSID;
	}

	vnt_control_out_u8(priv, MESSAGE_REQUEST_MACREG, MAC_REG_RCR, rx_mode);

	dev_dbg(&priv->usb->dev, "rx mode out= %x\n", rx_mode);
}