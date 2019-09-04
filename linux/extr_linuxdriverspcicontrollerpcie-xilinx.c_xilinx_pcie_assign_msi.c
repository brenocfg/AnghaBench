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

/* Variables and functions */
 int ENOSPC ; 
 int XILINX_NUM_MSI_IRQS ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msi_irq_in_use ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xilinx_pcie_assign_msi(void)
{
	int pos;

	pos = find_first_zero_bit(msi_irq_in_use, XILINX_NUM_MSI_IRQS);
	if (pos < XILINX_NUM_MSI_IRQS)
		set_bit(pos, msi_irq_in_use);
	else
		return -ENOSPC;

	return pos;
}