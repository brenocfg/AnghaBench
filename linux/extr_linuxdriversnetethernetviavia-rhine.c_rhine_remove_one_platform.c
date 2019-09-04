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
struct rhine_private {int /*<<< orphan*/  base; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int rhine_remove_one_platform(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct rhine_private *rp = netdev_priv(dev);

	unregister_netdev(dev);

	iounmap(rp->base);

	free_netdev(dev);

	return 0;
}