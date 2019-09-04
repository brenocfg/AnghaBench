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
struct TYPE_2__ {int /*<<< orphan*/ * callback_data; } ;
struct snd_dg00x {TYPE_1__ async_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_core_remove_address_handler (TYPE_1__*) ; 

void snd_dg00x_transaction_unregister(struct snd_dg00x *dg00x)
{
	if (dg00x->async_handler.callback_data == NULL)
		return;

	fw_core_remove_address_handler(&dg00x->async_handler);

	dg00x->async_handler.callback_data = NULL;
}