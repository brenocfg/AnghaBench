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
struct net_bridge {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  br_features_recompute (struct net_bridge*,int /*<<< orphan*/ ) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t br_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	struct net_bridge *br = netdev_priv(dev);

	return br_features_recompute(br, features);
}