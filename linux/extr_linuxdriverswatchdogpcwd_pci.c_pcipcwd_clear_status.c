#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_CLEAR_RESET_COUNT ; 
 scalar_t__ DEBUG ; 
 scalar_t__ VERBOSE ; 
 int WD_PCI_R2DS ; 
 int WD_PCI_WTRP ; 
 scalar_t__ debug ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 TYPE_1__ pcipcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  send_command (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int pcipcwd_clear_status(void)
{
	int control_status;
	int msb;
	int reset_counter;

	if (debug >= VERBOSE)
		pr_info("clearing watchdog trip status & LED\n");

	control_status = inb_p(pcipcwd_private.io_addr + 1);

	if (debug >= DEBUG) {
		pr_debug("status was: 0x%02x\n", control_status);
		pr_debug("sending: 0x%02x\n",
			 (control_status & WD_PCI_R2DS) | WD_PCI_WTRP);
	}

	/* clear trip status & LED and keep mode of relay 2 */
	outb_p((control_status & WD_PCI_R2DS) | WD_PCI_WTRP,
						pcipcwd_private.io_addr + 1);

	/* clear reset counter */
	msb = 0;
	reset_counter = 0xff;
	send_command(CMD_GET_CLEAR_RESET_COUNT, &msb, &reset_counter);

	if (debug >= DEBUG) {
		pr_debug("reset count was: 0x%02x\n", reset_counter);
	}

	return 0;
}