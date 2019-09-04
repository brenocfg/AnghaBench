#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int is_valid; } ;
union scu_remote_node_context {TYPE_1__ ssp; } ;
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  size_t u16 ;
struct isci_port {size_t physical_port_index; size_t reserved_rni; struct isci_host* owning_controller; } ;
struct isci_host {TYPE_2__* smu_registers; union scu_remote_node_context* remote_node_context_table; } ;
struct TYPE_4__ {int /*<<< orphan*/  interrupt_status; } ;

/* Variables and functions */
 size_t SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT ; 
 size_t SCU_CONTEXT_COMMAND_POST_RNC_32 ; 
 size_t SCU_CONTEXT_COMMAND_POST_RNC_SUSPEND_TX_RX ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_controller_post_request (struct isci_host*,size_t) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sci_port_post_dummy_remote_node(struct isci_port *iport)
{
	struct isci_host *ihost = iport->owning_controller;
	u8 phys_index = iport->physical_port_index;
	union scu_remote_node_context *rnc;
	u16 rni = iport->reserved_rni;
	u32 command;

	rnc = &ihost->remote_node_context_table[rni];
	rnc->ssp.is_valid = true;

	command = SCU_CONTEXT_COMMAND_POST_RNC_32 |
		  phys_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT | rni;

	sci_controller_post_request(ihost, command);

	/* ensure hardware has seen the post rnc command and give it
	 * ample time to act before sending the suspend
	 */
	readl(&ihost->smu_registers->interrupt_status); /* flush */
	udelay(10);

	command = SCU_CONTEXT_COMMAND_POST_RNC_SUSPEND_TX_RX |
		  phys_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT | rni;

	sci_controller_post_request(ihost, command);
}