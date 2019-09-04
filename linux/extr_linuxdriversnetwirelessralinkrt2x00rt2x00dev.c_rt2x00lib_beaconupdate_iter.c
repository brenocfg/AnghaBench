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
typedef  int /*<<< orphan*/  u8 ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_vif {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_WDS ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_is_usb (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00queue_update_beacon (struct rt2x00_dev*,struct ieee80211_vif*) ; 

__attribute__((used)) static void rt2x00lib_beaconupdate_iter(void *data, u8 *mac,
					struct ieee80211_vif *vif)
{
	struct rt2x00_dev *rt2x00dev = data;

	if (vif->type != NL80211_IFTYPE_AP &&
	    vif->type != NL80211_IFTYPE_ADHOC &&
	    vif->type != NL80211_IFTYPE_MESH_POINT &&
	    vif->type != NL80211_IFTYPE_WDS)
		return;

	/*
	 * Update the beacon without locking. This is safe on PCI devices
	 * as they only update the beacon periodically here. This should
	 * never be called for USB devices.
	 */
	WARN_ON(rt2x00_is_usb(rt2x00dev));
	rt2x00queue_update_beacon(rt2x00dev, vif);
}