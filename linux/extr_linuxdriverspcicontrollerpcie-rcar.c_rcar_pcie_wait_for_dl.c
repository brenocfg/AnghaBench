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
struct rcar_pcie {int dummy; } ;

/* Variables and functions */
 int DATA_LINK_ACTIVE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PCIETSTR ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int rcar_pci_read_reg (struct rcar_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rcar_pcie_wait_for_dl(struct rcar_pcie *pcie)
{
	unsigned int timeout = 10000;

	while (timeout--) {
		if ((rcar_pci_read_reg(pcie, PCIETSTR) & DATA_LINK_ACTIVE))
			return 0;

		udelay(5);
		cpu_relax();
	}

	return -ETIMEDOUT;
}