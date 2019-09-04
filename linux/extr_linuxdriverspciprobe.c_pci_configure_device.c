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
struct hotplug_params {int /*<<< orphan*/  t0; int /*<<< orphan*/  t1; int /*<<< orphan*/  t2; } ;
typedef  int /*<<< orphan*/  hpp ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct hotplug_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_configure_eetlp_prefix (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_configure_extended_tags (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_configure_ltr (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_configure_mps (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_configure_relaxed_ordering (struct pci_dev*) ; 
 int pci_get_hp_params (struct pci_dev*,struct hotplug_params*) ; 
 int /*<<< orphan*/  program_hpp_type0 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_hpp_type1 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_hpp_type2 (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_configure_device(struct pci_dev *dev)
{
	struct hotplug_params hpp;
	int ret;

	pci_configure_mps(dev);
	pci_configure_extended_tags(dev, NULL);
	pci_configure_relaxed_ordering(dev);
	pci_configure_ltr(dev);
	pci_configure_eetlp_prefix(dev);

	memset(&hpp, 0, sizeof(hpp));
	ret = pci_get_hp_params(dev, &hpp);
	if (ret)
		return;

	program_hpp_type2(dev, hpp.t2);
	program_hpp_type1(dev, hpp.t1);
	program_hpp_type0(dev, hpp.t0);
}