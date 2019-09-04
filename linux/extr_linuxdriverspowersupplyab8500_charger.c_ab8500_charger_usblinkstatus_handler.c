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
struct ab8500_charger {int /*<<< orphan*/  usb_link_status_work; int /*<<< orphan*/  charger_wq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ab8500_charger_usblinkstatus_handler(int irq, void *_di)
{
	struct ab8500_charger *di = _di;

	dev_dbg(di->dev, "USB link status changed\n");

	queue_work(di->charger_wq, &di->usb_link_status_work);

	return IRQ_HANDLED;
}