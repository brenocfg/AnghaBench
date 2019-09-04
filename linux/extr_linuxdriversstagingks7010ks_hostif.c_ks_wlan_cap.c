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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ preamble; scalar_t__ phy_type; } ;
struct ks_wlan_private {TYPE_1__ reg; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ D_11B_ONLY_MODE ; 
 scalar_t__ SHORT_PREAMBLE ; 
 int WLAN_CAPABILITY_DSSS_OFDM ; 
 int WLAN_CAPABILITY_PBCC ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int WLAN_CAPABILITY_SHORT_SLOT_TIME ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

__attribute__((used)) static __le16 ks_wlan_cap(struct ks_wlan_private *priv)
{
	u16 capability = 0x0000;

	if (priv->reg.preamble == SHORT_PREAMBLE)
		capability |= WLAN_CAPABILITY_SHORT_PREAMBLE;

	capability &= ~(WLAN_CAPABILITY_PBCC);	/* pbcc not support */

	if (priv->reg.phy_type != D_11B_ONLY_MODE) {
		capability |= WLAN_CAPABILITY_SHORT_SLOT_TIME;
		capability &= ~(WLAN_CAPABILITY_DSSS_OFDM);
	}

	return cpu_to_le16(capability);
}