#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tb {TYPE_1__* nhi; } ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int going_away; } ;

/* Variables and functions */
 int /*<<< orphan*/  nhi_enable_int_throttling (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_device_is_present (struct pci_dev*) ; 
 struct tb* pci_get_drvdata (struct pci_dev*) ; 
 int tb_domain_resume_noirq (struct tb*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int nhi_resume_noirq(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct tb *tb = pci_get_drvdata(pdev);

	/*
	 * Check that the device is still there. It may be that the user
	 * unplugged last device which causes the host controller to go
	 * away on PCs.
	 */
	if (!pci_device_is_present(pdev))
		tb->nhi->going_away = true;
	else
		nhi_enable_int_throttling(tb->nhi);

	return tb_domain_resume_noirq(tb);
}