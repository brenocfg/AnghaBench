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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fw_core_remove_address_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_register_handler ; 
 int /*<<< orphan*/  transaction_queues ; 

void snd_efw_transaction_unregister(void)
{
	WARN_ON(!list_empty(&transaction_queues));
	fw_core_remove_address_handler(&resp_register_handler);
}