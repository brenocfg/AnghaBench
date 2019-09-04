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
struct work_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ PDA_PSY_TO_CHANGE ; 
 scalar_t__ ac_status ; 
 scalar_t__ new_ac_status ; 
 scalar_t__ new_usb_status ; 
 int /*<<< orphan*/  pda_psy_ac ; 
 int /*<<< orphan*/  pda_psy_usb ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_status ; 

__attribute__((used)) static void supply_work_func(struct work_struct *work)
{
	if (ac_status == PDA_PSY_TO_CHANGE) {
		ac_status = new_ac_status;
		power_supply_changed(pda_psy_ac);
	}

	if (usb_status == PDA_PSY_TO_CHANGE) {
		usb_status = new_usb_status;
		power_supply_changed(pda_psy_usb);
	}
}