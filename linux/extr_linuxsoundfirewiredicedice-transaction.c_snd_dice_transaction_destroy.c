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
struct fw_address_handler {int /*<<< orphan*/ * callback_data; } ;
struct snd_dice {struct fw_address_handler notification_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_core_remove_address_handler (struct fw_address_handler*) ; 
 int /*<<< orphan*/  unregister_notification_address (struct snd_dice*) ; 

void snd_dice_transaction_destroy(struct snd_dice *dice)
{
	struct fw_address_handler *handler = &dice->notification_handler;

	if (handler->callback_data == NULL)
		return;

	unregister_notification_address(dice);

	fw_core_remove_address_handler(handler);
	handler->callback_data = NULL;
}