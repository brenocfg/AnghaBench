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
struct ipvl_dev {int sfeatures; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int IPVLAN_FEATURES ; 
 struct ipvl_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t ipvlan_fix_features(struct net_device *dev,
					     netdev_features_t features)
{
	struct ipvl_dev *ipvlan = netdev_priv(dev);

	return features & (ipvlan->sfeatures | ~IPVLAN_FEATURES);
}