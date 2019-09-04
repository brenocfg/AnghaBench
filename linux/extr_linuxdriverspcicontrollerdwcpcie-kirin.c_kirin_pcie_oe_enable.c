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
struct kirin_pcie {int /*<<< orphan*/  sysctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_DEBOUNCE_PARAM ; 
 int /*<<< orphan*/  PCIE_OE_BYPASS ; 
 int /*<<< orphan*/  SCTRL_PCIE_OE_OFFSET ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kirin_pcie_oe_enable(struct kirin_pcie *kirin_pcie)
{
	u32 val;

	regmap_read(kirin_pcie->sysctrl, SCTRL_PCIE_OE_OFFSET, &val);
	val |= PCIE_DEBOUNCE_PARAM;
	val &= ~PCIE_OE_BYPASS;
	regmap_write(kirin_pcie->sysctrl, SCTRL_PCIE_OE_OFFSET, val);
}