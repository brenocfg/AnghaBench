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
struct velocity_info {scalar_t__ pdev; void* mac_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_set_power_state (scalar_t__,char) ; 
 int /*<<< orphan*/  writeb (char,void*) ; 

__attribute__((used)) static void velocity_set_power_state(struct velocity_info *vptr, char state)
{
	void *addr = vptr->mac_regs;

	if (vptr->pdev)
		pci_set_power_state(vptr->pdev, state);
	else
		writeb(state, addr + 0x154);
}