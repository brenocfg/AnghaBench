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
 int /*<<< orphan*/  rpc_clients_block ; 
 int rpc_pipefs_notifier_register (int /*<<< orphan*/ *) ; 

int rpc_clients_notifier_register(void)
{
	return rpc_pipefs_notifier_register(&rpc_clients_block);
}