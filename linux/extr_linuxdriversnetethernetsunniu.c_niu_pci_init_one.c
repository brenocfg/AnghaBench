#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  device; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; } ;
union niu_parent_id {TYPE_1__ pci; } ;
typedef  int /*<<< orphan*/  u64 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
struct niu {int /*<<< orphan*/ * regs; int /*<<< orphan*/  parent; } ;
struct net_device {int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  irq; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  features; } ;
typedef  int /*<<< orphan*/  parent_id ;
struct TYPE_4__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_MODULE_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  NETIF_F_HIGHDMA ; 
 int /*<<< orphan*/  NIU_MAX_MTU ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_CERE ; 
 int PCI_EXP_DEVCTL_FERE ; 
 int PCI_EXP_DEVCTL_NFERE ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_NOSNOOP_EN ; 
 int PCI_EXP_DEVCTL_RELAX_EN ; 
 int PCI_EXP_DEVCTL_URRE ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLAT_TYPE_ATLAS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (union niu_parent_id*,int /*<<< orphan*/ ,int) ; 
 struct niu* netdev_priv (struct net_device*) ; 
 struct net_device* niu_alloc_and_init (int /*<<< orphan*/ *,struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_assign_netdev_ops (struct net_device*) ; 
 int /*<<< orphan*/  niu_device_announce (struct niu*) ; 
 int /*<<< orphan*/  niu_driver_version () ; 
 int niu_get_invariants (struct niu*) ; 
 int /*<<< orphan*/  niu_get_parent (struct niu*,union niu_parent_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_pci_ops ; 
 int /*<<< orphan*/  niu_put_parent (struct niu*) ; 
 int /*<<< orphan*/  niu_set_basic_features (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_2__*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/ * pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct net_device*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_clear_and_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int niu_pci_init_one(struct pci_dev *pdev,
			    const struct pci_device_id *ent)
{
	union niu_parent_id parent_id;
	struct net_device *dev;
	struct niu *np;
	int err;
	u64 dma_mask;

	niu_driver_version();

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "Cannot enable PCI device, aborting\n");
		return err;
	}

	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM) ||
	    !(pci_resource_flags(pdev, 2) & IORESOURCE_MEM)) {
		dev_err(&pdev->dev, "Cannot find proper PCI device base addresses, aborting\n");
		err = -ENODEV;
		goto err_out_disable_pdev;
	}

	err = pci_request_regions(pdev, DRV_MODULE_NAME);
	if (err) {
		dev_err(&pdev->dev, "Cannot obtain PCI resources, aborting\n");
		goto err_out_disable_pdev;
	}

	if (!pci_is_pcie(pdev)) {
		dev_err(&pdev->dev, "Cannot find PCI Express capability, aborting\n");
		err = -ENODEV;
		goto err_out_free_res;
	}

	dev = niu_alloc_and_init(&pdev->dev, pdev, NULL,
				 &niu_pci_ops, PCI_FUNC(pdev->devfn));
	if (!dev) {
		err = -ENOMEM;
		goto err_out_free_res;
	}
	np = netdev_priv(dev);

	memset(&parent_id, 0, sizeof(parent_id));
	parent_id.pci.domain = pci_domain_nr(pdev->bus);
	parent_id.pci.bus = pdev->bus->number;
	parent_id.pci.device = PCI_SLOT(pdev->devfn);

	np->parent = niu_get_parent(np, &parent_id,
				    PLAT_TYPE_ATLAS);
	if (!np->parent) {
		err = -ENOMEM;
		goto err_out_free_dev;
	}

	pcie_capability_clear_and_set_word(pdev, PCI_EXP_DEVCTL,
		PCI_EXP_DEVCTL_NOSNOOP_EN,
		PCI_EXP_DEVCTL_CERE | PCI_EXP_DEVCTL_NFERE |
		PCI_EXP_DEVCTL_FERE | PCI_EXP_DEVCTL_URRE |
		PCI_EXP_DEVCTL_RELAX_EN);

	dma_mask = DMA_BIT_MASK(44);
	err = pci_set_dma_mask(pdev, dma_mask);
	if (!err) {
		dev->features |= NETIF_F_HIGHDMA;
		err = pci_set_consistent_dma_mask(pdev, dma_mask);
		if (err) {
			dev_err(&pdev->dev, "Unable to obtain 44 bit DMA for consistent allocations, aborting\n");
			goto err_out_release_parent;
		}
	}
	if (err) {
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (err) {
			dev_err(&pdev->dev, "No usable DMA configuration, aborting\n");
			goto err_out_release_parent;
		}
	}

	niu_set_basic_features(dev);

	dev->priv_flags |= IFF_UNICAST_FLT;

	np->regs = pci_ioremap_bar(pdev, 0);
	if (!np->regs) {
		dev_err(&pdev->dev, "Cannot map device registers, aborting\n");
		err = -ENOMEM;
		goto err_out_release_parent;
	}

	pci_set_master(pdev);
	pci_save_state(pdev);

	dev->irq = pdev->irq;

	/* MTU range: 68 - 9216 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = NIU_MAX_MTU;

	niu_assign_netdev_ops(dev);

	err = niu_get_invariants(np);
	if (err) {
		if (err != -ENODEV)
			dev_err(&pdev->dev, "Problem fetching invariants of chip, aborting\n");
		goto err_out_iounmap;
	}

	err = register_netdev(dev);
	if (err) {
		dev_err(&pdev->dev, "Cannot register net device, aborting\n");
		goto err_out_iounmap;
	}

	pci_set_drvdata(pdev, dev);

	niu_device_announce(np);

	return 0;

err_out_iounmap:
	if (np->regs) {
		iounmap(np->regs);
		np->regs = NULL;
	}

err_out_release_parent:
	niu_put_parent(np);

err_out_free_dev:
	free_netdev(dev);

err_out_free_res:
	pci_release_regions(pdev);

err_out_disable_pdev:
	pci_disable_device(pdev);

	return err;
}