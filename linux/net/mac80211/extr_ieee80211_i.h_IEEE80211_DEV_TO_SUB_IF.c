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
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline struct ieee80211_sub_if_data *
IEEE80211_DEV_TO_SUB_IF(struct net_device *dev)
{
	return netdev_priv(dev);
}