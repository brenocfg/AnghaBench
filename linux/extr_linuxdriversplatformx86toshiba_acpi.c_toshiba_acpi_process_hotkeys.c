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
typedef  int u32 ;
struct toshiba_acpi_dev {int key_event_valid; int last_key_event; scalar_t__ system_event_supported; scalar_t__ info_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_SYSTEM_EVENT ; 
 int TOS_FIFO_EMPTY ; 
#define  TOS_NOT_SUPPORTED 129 
#define  TOS_SUCCESS 128 
 int hci_read (struct toshiba_acpi_dev*,int /*<<< orphan*/ ,int*) ; 
 int hci_write (struct toshiba_acpi_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int toshiba_acpi_query_hotkey (struct toshiba_acpi_dev*) ; 
 int /*<<< orphan*/  toshiba_acpi_report_hotkey (struct toshiba_acpi_dev*,int) ; 

__attribute__((used)) static void toshiba_acpi_process_hotkeys(struct toshiba_acpi_dev *dev)
{
	if (dev->info_supported) {
		int scancode = toshiba_acpi_query_hotkey(dev);

		if (scancode < 0) {
			pr_err("Failed to query hotkey event\n");
		} else if (scancode != 0) {
			toshiba_acpi_report_hotkey(dev, scancode);
			dev->key_event_valid = 1;
			dev->last_key_event = scancode;
		}
	} else if (dev->system_event_supported) {
		u32 result;
		u32 value;
		int retries = 3;

		do {
			result = hci_read(dev, HCI_SYSTEM_EVENT, &value);
			switch (result) {
			case TOS_SUCCESS:
				toshiba_acpi_report_hotkey(dev, (int)value);
				dev->key_event_valid = 1;
				dev->last_key_event = value;
				break;
			case TOS_NOT_SUPPORTED:
				/*
				 * This is a workaround for an unresolved
				 * issue on some machines where system events
				 * sporadically become disabled.
				 */
				result = hci_write(dev, HCI_SYSTEM_EVENT, 1);
				if (result == TOS_SUCCESS)
					pr_notice("Re-enabled hotkeys\n");
				/* Fall through */
			default:
				retries--;
				break;
			}
		} while (retries && result != TOS_FIFO_EMPTY);
	}
}