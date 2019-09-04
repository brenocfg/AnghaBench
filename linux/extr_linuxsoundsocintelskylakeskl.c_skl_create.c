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
struct skl {int /*<<< orphan*/  probe_work; struct pci_dev* pci; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hdac_io_ops {int dummy; } ;
struct hdac_bus {int use_posbuf; scalar_t__ bdl_pos_adj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_core_ops ; 
 struct skl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  skl_probe_work ; 
 struct hdac_bus* skl_to_bus (struct skl*) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_init (struct hdac_bus*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct hdac_io_ops const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int skl_create(struct pci_dev *pci,
		      const struct hdac_io_ops *io_ops,
		      struct skl **rskl)
{
	struct skl *skl;
	struct hdac_bus *bus;

	int err;

	*rskl = NULL;

	err = pci_enable_device(pci);
	if (err < 0)
		return err;

	skl = devm_kzalloc(&pci->dev, sizeof(*skl), GFP_KERNEL);
	if (!skl) {
		pci_disable_device(pci);
		return -ENOMEM;
	}

	bus = skl_to_bus(skl);
	snd_hdac_ext_bus_init(bus, &pci->dev, &bus_core_ops, io_ops, NULL);
	bus->use_posbuf = 1;
	skl->pci = pci;
	INIT_WORK(&skl->probe_work, skl_probe_work);
	bus->bdl_pos_adj = 0;

	*rskl = skl;

	return 0;
}