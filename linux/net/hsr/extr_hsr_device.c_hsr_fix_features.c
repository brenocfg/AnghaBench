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
struct hsr_priv {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  hsr_features_recompute (struct hsr_priv*,int /*<<< orphan*/ ) ; 
 struct hsr_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t hsr_fix_features(struct net_device *dev,
					  netdev_features_t features)
{
	struct hsr_priv *hsr = netdev_priv(dev);

	return hsr_features_recompute(hsr, features);
}