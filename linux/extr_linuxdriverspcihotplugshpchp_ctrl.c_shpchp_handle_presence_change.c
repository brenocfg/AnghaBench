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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct slot {scalar_t__ presence_save; TYPE_1__* hpc_ops; } ;
struct controller {int slot_device_offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_adapter_status ) (struct slot*,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INT_PRESENCE_OFF ; 
 int /*<<< orphan*/  INT_PRESENCE_ON ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_interrupt_event (struct slot*,int /*<<< orphan*/ ) ; 
 struct slot* shpchp_find_slot (struct controller*,int) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 
 int /*<<< orphan*/  stub1 (struct slot*,scalar_t__*) ; 

u8 shpchp_handle_presence_change(u8 hp_slot, struct controller *ctrl)
{
	struct slot *p_slot;
	u32 event_type;

	/* Presence Change */
	ctrl_dbg(ctrl, "Presence/Notify input change\n");

	p_slot = shpchp_find_slot(ctrl, hp_slot + ctrl->slot_device_offset);

	/*
	 * Save the presence state
	 */
	p_slot->hpc_ops->get_adapter_status(p_slot, &(p_slot->presence_save));
	if (p_slot->presence_save) {
		/*
		 * Card Present
		 */
		ctrl_info(ctrl, "Card present on Slot(%s)\n",
			  slot_name(p_slot));
		event_type = INT_PRESENCE_ON;
	} else {
		/*
		 * Not Present
		 */
		ctrl_info(ctrl, "Card not present on Slot(%s)\n",
			  slot_name(p_slot));
		event_type = INT_PRESENCE_OFF;
	}

	queue_interrupt_event(p_slot, event_type);

	return 1;
}