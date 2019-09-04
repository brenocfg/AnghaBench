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
typedef  union scu_remote_node_context {int dummy; } scu_remote_node_context ;
typedef  size_t u16 ;
struct isci_host {size_t remote_node_entries; union scu_remote_node_context* remote_node_context_table; scalar_t__* device_table; } ;

/* Variables and functions */

__attribute__((used)) static union scu_remote_node_context *sci_rnc_by_id(struct isci_host *ihost, u16 id)
{
	if (id < ihost->remote_node_entries &&
	    ihost->device_table[id])
		return &ihost->remote_node_context_table[id];

	return NULL;
}