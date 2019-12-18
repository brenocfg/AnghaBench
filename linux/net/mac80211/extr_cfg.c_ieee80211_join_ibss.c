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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct cfg80211_ibss_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int ieee80211_ibss_join (int /*<<< orphan*/ ,struct cfg80211_ibss_params*) ; 

__attribute__((used)) static int ieee80211_join_ibss(struct wiphy *wiphy, struct net_device *dev,
			       struct cfg80211_ibss_params *params)
{
	return ieee80211_ibss_join(IEEE80211_DEV_TO_SUB_IF(dev), params);
}