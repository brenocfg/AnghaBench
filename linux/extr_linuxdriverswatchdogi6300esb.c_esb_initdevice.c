#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  bootstatus; } ;
struct esb_dev {TYPE_4__ wdd; TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESB_CONFIG_REG ; 
 int /*<<< orphan*/  ESB_LOCK_REG ; 
 int /*<<< orphan*/  ESB_RELOAD_REG (struct esb_dev*) ; 
 int ESB_WDT_LOCK ; 
 int ESB_WDT_RELOAD ; 
 int ESB_WDT_TIMEOUT ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  esb_timer_set_heartbeat (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esb_unlock_registers (struct esb_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esb_initdevice(struct esb_dev *edev)
{
	u8 val1;
	u16 val2;

	/*
	 * Config register:
	 * Bit    5 : 0 = Enable WDT_OUTPUT
	 * Bit    2 : 0 = set the timer frequency to the PCI clock
	 * divided by 2^15 (approx 1KHz).
	 * Bits 1:0 : 11 = WDT_INT_TYPE Disabled.
	 * The watchdog has two timers, it can be setup so that the
	 * expiry of timer1 results in an interrupt and the expiry of
	 * timer2 results in a reboot. We set it to not generate
	 * any interrupts as there is not much we can do with it
	 * right now.
	 */
	pci_write_config_word(edev->pdev, ESB_CONFIG_REG, 0x0003);

	/* Check that the WDT isn't already locked */
	pci_read_config_byte(edev->pdev, ESB_LOCK_REG, &val1);
	if (val1 & ESB_WDT_LOCK)
		dev_warn(&edev->pdev->dev, "nowayout already set\n");

	/* Set the timer to watchdog mode and disable it for now */
	pci_write_config_byte(edev->pdev, ESB_LOCK_REG, 0x00);

	/* Check if the watchdog was previously triggered */
	esb_unlock_registers(edev);
	val2 = readw(ESB_RELOAD_REG(edev));
	if (val2 & ESB_WDT_TIMEOUT)
		edev->wdd.bootstatus = WDIOF_CARDRESET;

	/* Reset WDT_TIMEOUT flag and timers */
	esb_unlock_registers(edev);
	writew((ESB_WDT_TIMEOUT | ESB_WDT_RELOAD), ESB_RELOAD_REG(edev));

	/* And set the correct timeout value */
	esb_timer_set_heartbeat(&edev->wdd, edev->wdd.timeout);
}