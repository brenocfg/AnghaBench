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
struct pci_dev {scalar_t__ shpc_managed; } ;
struct controller {TYPE_1__* hpc_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release_ctlr ) (struct controller*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct controller*) ; 
 struct controller* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  shpchp_remove_ctrl_files (struct controller*) ; 
 int /*<<< orphan*/  stub1 (struct controller*) ; 

__attribute__((used)) static void shpc_remove(struct pci_dev *dev)
{
	struct controller *ctrl = pci_get_drvdata(dev);

	dev->shpc_managed = 0;
	shpchp_remove_ctrl_files(ctrl);
	ctrl->hpc_ops->release_ctlr(ctrl);
	kfree(ctrl);
}