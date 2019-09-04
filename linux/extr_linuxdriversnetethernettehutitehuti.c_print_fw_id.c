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
struct pci_nic {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ FW_VER ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void print_fw_id(struct pci_nic *nic)
{
	pr_info("fw 0x%x\n", readl(nic->regs + FW_VER));
}