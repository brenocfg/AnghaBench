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
struct TYPE_2__ {int boot_status; scalar_t__ supports_temp; scalar_t__ io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_FIRMWARE_VERSION ; 
 int WDIOF_CARDRESET ; 
 int WDIOF_OVERHEAT ; 
 int pcipcwd_get_option_switches () ; 
 TYPE_1__ pcipcwd_private ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int send_command (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void pcipcwd_show_card_info(void)
{
	int got_fw_rev, fw_rev_major, fw_rev_minor;
	char fw_ver_str[20];		/* The cards firmware version */
	int option_switches;

	got_fw_rev = send_command(CMD_GET_FIRMWARE_VERSION, &fw_rev_major,
								&fw_rev_minor);
	if (got_fw_rev)
		sprintf(fw_ver_str, "%u.%02u", fw_rev_major, fw_rev_minor);
	else
		sprintf(fw_ver_str, "<card no answer>");

	/* Get switch settings */
	option_switches = pcipcwd_get_option_switches();

	pr_info("Found card at port 0x%04x (Firmware: %s) %s temp option\n",
		(int) pcipcwd_private.io_addr, fw_ver_str,
		(pcipcwd_private.supports_temp ? "with" : "without"));

	pr_info("Option switches (0x%02x): Temperature Reset Enable=%s, Power On Delay=%s\n",
		option_switches,
		((option_switches & 0x10) ? "ON" : "OFF"),
		((option_switches & 0x08) ? "ON" : "OFF"));

	if (pcipcwd_private.boot_status & WDIOF_CARDRESET)
		pr_info("Previous reset was caused by the Watchdog card\n");

	if (pcipcwd_private.boot_status & WDIOF_OVERHEAT)
		pr_info("Card sensed a CPU Overheat\n");

	if (pcipcwd_private.boot_status == 0)
		pr_info("No previous trip detected - Cold boot or reset\n");
}