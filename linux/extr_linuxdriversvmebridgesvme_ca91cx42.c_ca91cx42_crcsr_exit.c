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
typedef  int /*<<< orphan*/  u32 ;
struct vme_bridge {struct ca91cx42_driver* driver_priv; } ;
struct pci_dev {int dummy; } ;
struct ca91cx42_driver {int /*<<< orphan*/  crcsr_bus; int /*<<< orphan*/  crcsr_kernel; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA91CX42_VCSR_CTL_EN ; 
 scalar_t__ VCSR_CTL ; 
 scalar_t__ VCSR_TO ; 
 int /*<<< orphan*/  VME_CRCSR_BUF_SIZE ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca91cx42_crcsr_exit(struct vme_bridge *ca91cx42_bridge,
	struct pci_dev *pdev)
{
	u32 tmp;
	struct ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	/* Turn off CR/CSR space */
	tmp = ioread32(bridge->base + VCSR_CTL);
	tmp &= ~CA91CX42_VCSR_CTL_EN;
	iowrite32(tmp, bridge->base + VCSR_CTL);

	/* Free image */
	iowrite32(0, bridge->base + VCSR_TO);

	pci_free_consistent(pdev, VME_CRCSR_BUF_SIZE, bridge->crcsr_kernel,
		bridge->crcsr_bus);
}