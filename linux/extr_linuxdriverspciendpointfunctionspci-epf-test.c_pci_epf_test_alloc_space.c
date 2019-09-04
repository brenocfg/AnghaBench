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
struct pci_epf_test_reg {int dummy; } ;
struct pci_epf_test {int test_reg_bar; void** reg; } ;
struct device {int dummy; } ;
struct pci_epf {struct device dev; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int BAR_0 ; 
 int BAR_5 ; 
 int ENOMEM ; 
 int* bar_size ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct pci_epf_test* epf_get_drvdata (struct pci_epf*) ; 
 void* pci_epf_alloc_space (struct pci_epf*,int,int) ; 

__attribute__((used)) static int pci_epf_test_alloc_space(struct pci_epf *epf)
{
	struct pci_epf_test *epf_test = epf_get_drvdata(epf);
	struct device *dev = &epf->dev;
	void *base;
	int bar;
	enum pci_barno test_reg_bar = epf_test->test_reg_bar;

	base = pci_epf_alloc_space(epf, sizeof(struct pci_epf_test_reg),
				   test_reg_bar);
	if (!base) {
		dev_err(dev, "Failed to allocated register space\n");
		return -ENOMEM;
	}
	epf_test->reg[test_reg_bar] = base;

	for (bar = BAR_0; bar <= BAR_5; bar++) {
		if (bar == test_reg_bar)
			continue;
		base = pci_epf_alloc_space(epf, bar_size[bar], bar);
		if (!base)
			dev_err(dev, "Failed to allocate space for BAR%d\n",
				bar);
		epf_test->reg[bar] = base;
	}

	return 0;
}