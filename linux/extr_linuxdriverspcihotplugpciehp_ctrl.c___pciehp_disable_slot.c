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
typedef  scalar_t__ u8 ;
struct slot {struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ POWER_CTRL (struct controller*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciehp_get_power_status (struct slot*,scalar_t__*) ; 
 int /*<<< orphan*/  remove_board (struct slot*) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 

__attribute__((used)) static int __pciehp_disable_slot(struct slot *p_slot)
{
	u8 getstatus = 0;
	struct controller *ctrl = p_slot->ctrl;

	if (POWER_CTRL(p_slot->ctrl)) {
		pciehp_get_power_status(p_slot, &getstatus);
		if (!getstatus) {
			ctrl_info(ctrl, "Slot(%s): Already disabled\n",
				  slot_name(p_slot));
			return -EINVAL;
		}
	}

	remove_board(p_slot);
	return 0;
}