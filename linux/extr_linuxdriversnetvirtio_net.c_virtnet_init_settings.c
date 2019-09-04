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
struct virtnet_info {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void virtnet_init_settings(struct net_device *dev)
{
	struct virtnet_info *vi = netdev_priv(dev);

	vi->speed = SPEED_UNKNOWN;
	vi->duplex = DUPLEX_UNKNOWN;
}