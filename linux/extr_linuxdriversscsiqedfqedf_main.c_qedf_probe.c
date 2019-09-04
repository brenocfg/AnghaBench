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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_MODE_NORMAL ; 
 int __qedf_probe (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedf_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	return __qedf_probe(pdev, QEDF_MODE_NORMAL);
}