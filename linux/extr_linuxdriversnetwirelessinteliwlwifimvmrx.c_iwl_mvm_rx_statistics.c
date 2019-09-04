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
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_handle_rx_statistics (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_rx_statistics(struct iwl_mvm *mvm, struct iwl_rx_cmd_buffer *rxb)
{
	iwl_mvm_handle_rx_statistics(mvm, rxb_addr(rxb));
}