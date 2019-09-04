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
struct mvebu_pcie_port {int dummy; } ;

/* Variables and functions */
 int PCIE_STAT_LINK_DOWN ; 
 int /*<<< orphan*/  PCIE_STAT_OFF ; 
 int mvebu_readl (struct mvebu_pcie_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mvebu_pcie_link_up(struct mvebu_pcie_port *port)
{
	return !(mvebu_readl(port, PCIE_STAT_OFF) & PCIE_STAT_LINK_DOWN);
}