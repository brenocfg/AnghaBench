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
 scalar_t__ DEBUG ; 
 int ISA_COMMAND_TIMEOUT ; 
 int WD_WCMD ; 
 scalar_t__ debug ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 TYPE_1__ pcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int send_isa_command(int cmd)
{
	int i;
	int control_status;
	int port0, last_port0;	/* Double read for stabilising */

	if (debug >= DEBUG)
		pr_debug("sending following data cmd=0x%02x\n", cmd);

	/* The WCMD bit must be 1 and the command is only 4 bits in size */
	control_status = (cmd & 0x0F) | WD_WCMD;
	outb_p(control_status, pcwd_private.io_addr + 2);
	udelay(ISA_COMMAND_TIMEOUT);

	port0 = inb_p(pcwd_private.io_addr);
	for (i = 0; i < 25; ++i) {
		last_port0 = port0;
		port0 = inb_p(pcwd_private.io_addr);

		if (port0 == last_port0)
			break;	/* Data is stable */

		udelay(250);
	}

	if (debug >= DEBUG)
		pr_debug("received following data for cmd=0x%02x: port0=0x%02x last_port0=0x%02x\n",
			 cmd, port0, last_port0);

	return port0;
}