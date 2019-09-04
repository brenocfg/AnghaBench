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
struct aer_header_log_regs {int /*<<< orphan*/  dw3; int /*<<< orphan*/  dw2; int /*<<< orphan*/  dw1; int /*<<< orphan*/  dw0; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __print_tlp_header(struct pci_dev *dev,
			       struct aer_header_log_regs *t)
{
	pci_err(dev, "  TLP Header: %08x %08x %08x %08x\n",
		t->dw0, t->dw1, t->dw2, t->dw3);
}