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
typedef  int /*<<< orphan*/  u16 ;
struct sci_remote_node_context {int /*<<< orphan*/  sm; int /*<<< orphan*/  destination_state; int /*<<< orphan*/  remote_node_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNC_DEST_UNSPECIFIED ; 
 int /*<<< orphan*/  SCI_RNC_INITIAL ; 
 int /*<<< orphan*/  memset (struct sci_remote_node_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_init_sm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_remote_node_context_state_table ; 

void sci_remote_node_context_construct(struct sci_remote_node_context *rnc,
					    u16 remote_node_index)
{
	memset(rnc, 0, sizeof(struct sci_remote_node_context));

	rnc->remote_node_index = remote_node_index;
	rnc->destination_state = RNC_DEST_UNSPECIFIED;

	sci_init_sm(&rnc->sm, sci_remote_node_context_state_table, SCI_RNC_INITIAL);
}