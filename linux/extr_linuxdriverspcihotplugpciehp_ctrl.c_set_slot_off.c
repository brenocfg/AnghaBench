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
struct slot {int dummy; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 scalar_t__ POWER_CTRL (struct controller*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pciehp_green_led_off (struct slot*) ; 
 int /*<<< orphan*/  pciehp_power_off_slot (struct slot*) ; 
 int /*<<< orphan*/  pciehp_set_attention_status (struct slot*,int) ; 

__attribute__((used)) static void set_slot_off(struct controller *ctrl, struct slot *pslot)
{
	/* turn off slot, turn on Amber LED, turn off Green LED if supported*/
	if (POWER_CTRL(ctrl)) {
		pciehp_power_off_slot(pslot);

		/*
		 * After turning power off, we must wait for at least 1 second
		 * before taking any action that relies on power having been
		 * removed from the slot/adapter.
		 */
		msleep(1000);
	}

	pciehp_green_led_off(pslot);
	pciehp_set_attention_status(pslot, 1);
}