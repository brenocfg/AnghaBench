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
struct iproc_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPROC_PCIE_INTX_EN ; 
 int /*<<< orphan*/  SYS_RC_INTX_MASK ; 
 int /*<<< orphan*/  iproc_pcie_write_reg (struct iproc_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iproc_pcie_enable(struct iproc_pcie *pcie)
{
	iproc_pcie_write_reg(pcie, IPROC_PCIE_INTX_EN, SYS_RC_INTX_MASK);
}