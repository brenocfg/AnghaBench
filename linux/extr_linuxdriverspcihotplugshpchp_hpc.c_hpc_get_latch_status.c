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
typedef  int u32 ;
struct slot {int /*<<< orphan*/  hp_slot; struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 int MRL_SENSOR ; 
 int /*<<< orphan*/  SLOT_REG (int /*<<< orphan*/ ) ; 
 int shpc_readl (struct controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpc_get_latch_status(struct slot *slot, u8 *status)
{
	struct controller *ctrl = slot->ctrl;
	u32 slot_reg = shpc_readl(ctrl, SLOT_REG(slot->hp_slot));

	*status = !!(slot_reg & MRL_SENSOR);	/* 0 -> close; 1 -> open */

	return 0;
}