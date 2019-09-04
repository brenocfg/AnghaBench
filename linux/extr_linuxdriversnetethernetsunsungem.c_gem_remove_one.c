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
struct gem_init_block {int dummy; } ;
struct gem {int /*<<< orphan*/  regs; int /*<<< orphan*/  gblock_dvma; int /*<<< orphan*/  init_block; int /*<<< orphan*/  reset_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void gem_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);

	if (dev) {
		struct gem *gp = netdev_priv(dev);

		unregister_netdev(dev);

		/* Ensure reset task is truly gone */
		cancel_work_sync(&gp->reset_task);

		/* Free resources */
		pci_free_consistent(pdev,
				    sizeof(struct gem_init_block),
				    gp->init_block,
				    gp->gblock_dvma);
		iounmap(gp->regs);
		pci_release_regions(pdev);
		free_netdev(dev);
	}
}