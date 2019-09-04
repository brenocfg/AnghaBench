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
struct vnt_private {scalar_t__ hw; scalar_t__ pcid; scalar_t__ PortOffset; scalar_t__ mac_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_hw (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (scalar_t__) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (scalar_t__) ; 

__attribute__((used)) static void device_free_info(struct vnt_private *priv)
{
	if (!priv)
		return;

	if (priv->mac_hw)
		ieee80211_unregister_hw(priv->hw);

	if (priv->PortOffset)
		iounmap(priv->PortOffset);

	if (priv->pcid)
		pci_release_regions(priv->pcid);

	if (priv->hw)
		ieee80211_free_hw(priv->hw);
}