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
struct fw_address_handler {int length; struct snd_dice* callback_data; int /*<<< orphan*/  address_callback; } ;
struct snd_dice {struct fw_address_handler notification_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  dice_notification ; 
 int fw_core_add_address_handler (struct fw_address_handler*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_core_remove_address_handler (struct fw_address_handler*) ; 
 int /*<<< orphan*/  fw_high_memory_region ; 
 int get_subaddrs (struct snd_dice*) ; 
 int register_notification_address (struct snd_dice*,int) ; 

int snd_dice_transaction_init(struct snd_dice *dice)
{
	struct fw_address_handler *handler = &dice->notification_handler;
	int err;

	err = get_subaddrs(dice);
	if (err < 0)
		return err;

	/* Allocation callback in address space over host controller */
	handler->length = 4;
	handler->address_callback = dice_notification;
	handler->callback_data = dice;
	err = fw_core_add_address_handler(handler, &fw_high_memory_region);
	if (err < 0) {
		handler->callback_data = NULL;
		return err;
	}

	/* Register the address space */
	err = register_notification_address(dice, true);
	if (err < 0) {
		fw_core_remove_address_handler(handler);
		handler->callback_data = NULL;
	}

	return err;
}