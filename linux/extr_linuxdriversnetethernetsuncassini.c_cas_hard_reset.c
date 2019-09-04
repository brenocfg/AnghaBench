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
struct cas {int /*<<< orphan*/  pdev; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIM_LOCAL_DEV_SOFT_0 ; 
 scalar_t__ REG_BIM_LOCAL_DEV_EN ; 
 int /*<<< orphan*/  pci_restore_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cas_hard_reset(struct cas *cp)
{
	writel(BIM_LOCAL_DEV_SOFT_0, cp->regs + REG_BIM_LOCAL_DEV_EN);
	udelay(20);
	pci_restore_state(cp->pdev);
}