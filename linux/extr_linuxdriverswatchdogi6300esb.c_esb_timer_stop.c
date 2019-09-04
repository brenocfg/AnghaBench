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
typedef  int u8 ;
struct watchdog_device {int dummy; } ;
struct esb_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESB_LOCK_REG ; 
 int /*<<< orphan*/  ESB_RELOAD_REG (struct esb_dev*) ; 
 int ESB_WDT_ENABLE ; 
 int /*<<< orphan*/  ESB_WDT_RELOAD ; 
 int /*<<< orphan*/  esb_unlock_registers (struct esb_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct esb_dev* to_esb_dev (struct watchdog_device*) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esb_timer_stop(struct watchdog_device *wdd)
{
	struct esb_dev *edev = to_esb_dev(wdd);
	u8 val;

	/* First, reset timers as suggested by the docs */
	esb_unlock_registers(edev);
	writew(ESB_WDT_RELOAD, ESB_RELOAD_REG(edev));
	/* Then disable the WDT */
	pci_write_config_byte(edev->pdev, ESB_LOCK_REG, 0x0);
	pci_read_config_byte(edev->pdev, ESB_LOCK_REG, &val);

	/* Returns 0 if the timer was disabled, non-zero otherwise */
	return val & ESB_WDT_ENABLE;
}