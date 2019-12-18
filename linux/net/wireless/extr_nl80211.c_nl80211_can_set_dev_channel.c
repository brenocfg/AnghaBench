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
struct wireless_dev {scalar_t__ iftype; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ NL80211_IFTYPE_P2P_GO ; 

__attribute__((used)) static bool nl80211_can_set_dev_channel(struct wireless_dev *wdev)
{
	/*
	 * You can only set the channel explicitly for WDS interfaces,
	 * all others have their channel managed via their respective
	 * "establish a connection" command (connect, join, ...)
	 *
	 * For AP/GO and mesh mode, the channel can be set with the
	 * channel userspace API, but is only stored and passed to the
	 * low-level driver when the AP starts or the mesh is joined.
	 * This is for backward compatibility, userspace can also give
	 * the channel in the start-ap or join-mesh commands instead.
	 *
	 * Monitors are special as they are normally slaved to
	 * whatever else is going on, so they have their own special
	 * operation to set the monitor channel if possible.
	 */
	return !wdev ||
		wdev->iftype == NL80211_IFTYPE_AP ||
		wdev->iftype == NL80211_IFTYPE_MESH_POINT ||
		wdev->iftype == NL80211_IFTYPE_MONITOR ||
		wdev->iftype == NL80211_IFTYPE_P2P_GO;
}