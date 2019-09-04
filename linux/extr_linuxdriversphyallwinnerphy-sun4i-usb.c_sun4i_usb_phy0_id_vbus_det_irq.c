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
struct sun4i_usb_phy_data {int /*<<< orphan*/  detect; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBOUNCE_TIME ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static irqreturn_t sun4i_usb_phy0_id_vbus_det_irq(int irq, void *dev_id)
{
	struct sun4i_usb_phy_data *data = dev_id;

	/* vbus or id changed, let the pins settle and then scan them */
	mod_delayed_work(system_wq, &data->detect, DEBOUNCE_TIME);

	return IRQ_HANDLED;
}