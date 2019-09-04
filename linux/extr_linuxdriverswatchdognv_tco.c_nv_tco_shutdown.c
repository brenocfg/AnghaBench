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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCP51_SMBUS_SETUP_B ; 
 int /*<<< orphan*/  MCP51_SMBUS_SETUP_B_TCO_REBOOT ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tco_pci ; 
 int /*<<< orphan*/  tco_timer_stop () ; 

__attribute__((used)) static void nv_tco_shutdown(struct platform_device *dev)
{
	u32 val;

	tco_timer_stop();

	/* Some BIOSes fail the POST (once) if the NO_REBOOT flag is not
	 * unset during shutdown. */
	pci_read_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, &val);
	val &= ~MCP51_SMBUS_SETUP_B_TCO_REBOOT;
	pci_write_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, val);
}