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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct rockchip_pcie_ep {int /*<<< orphan*/  rockchip; } ;

/* Variables and functions */
 int EINVAL ; 
 int PCI_COMMAND_INTX_DISABLE ; 
 scalar_t__ ROCKCHIP_PCIE_EP_CMD_STATUS ; 
 scalar_t__ ROCKCHIP_PCIE_EP_FUNC_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rockchip_pcie_ep_assert_intx (struct rockchip_pcie_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rockchip_pcie_read (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int rockchip_pcie_ep_send_legacy_irq(struct rockchip_pcie_ep *ep, u8 fn,
					    u8 intx)
{
	u16 cmd;

	cmd = rockchip_pcie_read(&ep->rockchip,
				 ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				 ROCKCHIP_PCIE_EP_CMD_STATUS);

	if (cmd & PCI_COMMAND_INTX_DISABLE)
		return -EINVAL;

	/*
	 * Should add some delay between toggling INTx per TRM vaguely saying
	 * it depends on some cycles of the AHB bus clock to function it. So
	 * add sufficient 1ms here.
	 */
	rockchip_pcie_ep_assert_intx(ep, fn, intx, true);
	mdelay(1);
	rockchip_pcie_ep_assert_intx(ep, fn, intx, false);
	return 0;
}