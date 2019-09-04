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
struct ath6kl_vif {struct ath6kl* ar; } ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 scalar_t__ netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline struct ath6kl *ath6kl_priv(struct net_device *dev)
{
	return ((struct ath6kl_vif *) netdev_priv(dev))->ar;
}