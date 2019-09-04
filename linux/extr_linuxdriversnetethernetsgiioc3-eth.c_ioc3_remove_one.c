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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct ioc3_private {int /*<<< orphan*/  ioc3_timer; struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (struct ioc3*) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void ioc3_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3 *ioc3 = ip->regs;

	unregister_netdev(dev);
	del_timer_sync(&ip->ioc3_timer);

	iounmap(ioc3);
	pci_release_regions(pdev);
	free_netdev(dev);
	/*
	 * We should call pci_disable_device(pdev); here if the IOC3 wasn't
	 * such a weird device ...
	 */
}