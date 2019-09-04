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
typedef  int u32 ;
struct mvebu_pcie_port {int dummy; } ;

/* Variables and functions */
 int PCIE_STAT_DEV ; 
 int /*<<< orphan*/  PCIE_STAT_OFF ; 
 int mvebu_readl (struct mvebu_pcie_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_writel (struct mvebu_pcie_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvebu_pcie_set_local_dev_nr(struct mvebu_pcie_port *port, int nr)
{
	u32 stat;

	stat = mvebu_readl(port, PCIE_STAT_OFF);
	stat &= ~PCIE_STAT_DEV;
	stat |= nr << 16;
	mvebu_writel(port, stat, PCIE_STAT_OFF);
}