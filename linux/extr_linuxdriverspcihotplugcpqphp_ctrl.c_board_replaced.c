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
struct pci_func {int device; int status; } ;
struct pci_bus {int cur_bus_speed; } ;
struct controller {int slot_device_offset; int /*<<< orphan*/  crit_sect; scalar_t__ hpc_reg; struct pci_bus* pci_bus; } ;

/* Variables and functions */
 int CARD_FUNCTIONING ; 
 int HZ ; 
 int INTERLOCK_OPEN ; 
 scalar_t__ INT_INPUT_CLEAR ; 
 int POWER_FAILURE ; 
 scalar_t__ SLOT_POWER ; 
 int WRONG_BUS_FREQUENCY ; 
 int /*<<< orphan*/  amber_LED_off (struct controller*,int) ; 
 int /*<<< orphan*/  amber_LED_on (struct controller*,int) ; 
 int cpqhp_configure_board (struct controller*,struct pci_func*) ; 
 int cpqhp_valid_replace (struct controller*,struct pci_func*) ; 
 int /*<<< orphan*/  disable_slot_power (struct controller*,int) ; 
 int /*<<< orphan*/  enable_slot_power (struct controller*,int) ; 
 int get_adapter_speed (struct controller*,int) ; 
 int /*<<< orphan*/  green_LED_blink (struct controller*,int) ; 
 int /*<<< orphan*/  green_LED_off (struct controller*,int) ; 
 scalar_t__ is_slot_enabled (struct controller*,int) ; 
 int /*<<< orphan*/  long_delay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readb (scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  set_SOGO (struct controller*) ; 
 scalar_t__ set_controller_speed (struct controller*,int,int) ; 
 int /*<<< orphan*/  slot_disable (struct controller*,int) ; 
 int /*<<< orphan*/  slot_enable (struct controller*,int) ; 
 int /*<<< orphan*/  wait_for_ctrl_irq (struct controller*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static u32 board_replaced(struct pci_func *func, struct controller *ctrl)
{
	struct pci_bus *bus = ctrl->pci_bus;
	u8 hp_slot;
	u8 temp_byte;
	u8 adapter_speed;
	u32 rc = 0;

	hp_slot = func->device - ctrl->slot_device_offset;

	/*
	 * The switch is open.
	 */
	if (readl(ctrl->hpc_reg + INT_INPUT_CLEAR) & (0x01L << hp_slot))
		rc = INTERLOCK_OPEN;
	/*
	 * The board is already on
	 */
	else if (is_slot_enabled(ctrl, hp_slot))
		rc = CARD_FUNCTIONING;
	else {
		mutex_lock(&ctrl->crit_sect);

		/* turn on board without attaching to the bus */
		enable_slot_power(ctrl, hp_slot);

		set_SOGO(ctrl);

		/* Wait for SOBS to be unset */
		wait_for_ctrl_irq(ctrl);

		/* Change bits in slot power register to force another shift out
		 * NOTE: this is to work around the timer bug */
		temp_byte = readb(ctrl->hpc_reg + SLOT_POWER);
		writeb(0x00, ctrl->hpc_reg + SLOT_POWER);
		writeb(temp_byte, ctrl->hpc_reg + SLOT_POWER);

		set_SOGO(ctrl);

		/* Wait for SOBS to be unset */
		wait_for_ctrl_irq(ctrl);

		adapter_speed = get_adapter_speed(ctrl, hp_slot);
		if (bus->cur_bus_speed != adapter_speed)
			if (set_controller_speed(ctrl, adapter_speed, hp_slot))
				rc = WRONG_BUS_FREQUENCY;

		/* turn off board without attaching to the bus */
		disable_slot_power(ctrl, hp_slot);

		set_SOGO(ctrl);

		/* Wait for SOBS to be unset */
		wait_for_ctrl_irq(ctrl);

		mutex_unlock(&ctrl->crit_sect);

		if (rc)
			return rc;

		mutex_lock(&ctrl->crit_sect);

		slot_enable(ctrl, hp_slot);
		green_LED_blink(ctrl, hp_slot);

		amber_LED_off(ctrl, hp_slot);

		set_SOGO(ctrl);

		/* Wait for SOBS to be unset */
		wait_for_ctrl_irq(ctrl);

		mutex_unlock(&ctrl->crit_sect);

		/* Wait for ~1 second because of hot plug spec */
		long_delay(1*HZ);

		/* Check for a power fault */
		if (func->status == 0xFF) {
			/* power fault occurred, but it was benign */
			rc = POWER_FAILURE;
			func->status = 0;
		} else
			rc = cpqhp_valid_replace(ctrl, func);

		if (!rc) {
			/* It must be the same board */

			rc = cpqhp_configure_board(ctrl, func);

			/* If configuration fails, turn it off
			 * Get slot won't work for devices behind
			 * bridges, but in this case it will always be
			 * called for the "base" bus/dev/func of an
			 * adapter.
			 */

			mutex_lock(&ctrl->crit_sect);

			amber_LED_on(ctrl, hp_slot);
			green_LED_off(ctrl, hp_slot);
			slot_disable(ctrl, hp_slot);

			set_SOGO(ctrl);

			/* Wait for SOBS to be unset */
			wait_for_ctrl_irq(ctrl);

			mutex_unlock(&ctrl->crit_sect);

			if (rc)
				return rc;
			else
				return 1;

		} else {
			/* Something is wrong

			 * Get slot won't work for devices behind bridges, but
			 * in this case it will always be called for the "base"
			 * bus/dev/func of an adapter.
			 */

			mutex_lock(&ctrl->crit_sect);

			amber_LED_on(ctrl, hp_slot);
			green_LED_off(ctrl, hp_slot);
			slot_disable(ctrl, hp_slot);

			set_SOGO(ctrl);

			/* Wait for SOBS to be unset */
			wait_for_ctrl_irq(ctrl);

			mutex_unlock(&ctrl->crit_sect);
		}

	}
	return rc;

}