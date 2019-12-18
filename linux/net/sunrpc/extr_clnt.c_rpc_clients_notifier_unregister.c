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
 void rpc_pipefs_notifier_unregister (int /*<<< orphan*/ *) ; 

void rpc_clients_notifier_unregister(void)
{
	return rpc_pipefs_notifier_unregister(&rpc_clients_block);
}