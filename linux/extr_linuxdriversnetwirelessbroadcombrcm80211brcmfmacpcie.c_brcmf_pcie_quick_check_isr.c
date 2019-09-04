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
struct brcmf_pciedev_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_PCIE_PCIE2REG_MAILBOXINT ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_pcie_intr_disable (struct brcmf_pciedev_info*) ; 
 scalar_t__ brcmf_pcie_read_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t brcmf_pcie_quick_check_isr(int irq, void *arg)
{
	struct brcmf_pciedev_info *devinfo = (struct brcmf_pciedev_info *)arg;

	if (brcmf_pcie_read_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT)) {
		brcmf_pcie_intr_disable(devinfo);
		brcmf_dbg(PCIE, "Enter\n");
		return IRQ_WAKE_THREAD;
	}
	return IRQ_NONE;
}