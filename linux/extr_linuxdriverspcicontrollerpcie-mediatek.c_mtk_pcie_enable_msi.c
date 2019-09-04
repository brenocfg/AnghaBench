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
struct mtk_pcie_port {scalar_t__ base; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSI_MASK ; 
 scalar_t__ PCIE_IMSI_ADDR ; 
 scalar_t__ PCIE_INT_MASK ; 
 scalar_t__ PCIE_MSI_VECTOR ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  virt_to_phys (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_pcie_enable_msi(struct mtk_pcie_port *port)
{
	u32 val;
	phys_addr_t msg_addr;

	msg_addr = virt_to_phys(port->base + PCIE_MSI_VECTOR);
	val = lower_32_bits(msg_addr);
	writel(val, port->base + PCIE_IMSI_ADDR);

	val = readl(port->base + PCIE_INT_MASK);
	val &= ~MSI_MASK;
	writel(val, port->base + PCIE_INT_MASK);
}