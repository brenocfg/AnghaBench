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
typedef  int u32 ;
typedef  void* u16 ;
struct sci_remote_node_table {void* group_array_size; void* available_nodes_array_size; int /*<<< orphan*/  remote_node_groups; int /*<<< orphan*/  available_remote_nodes; } ;

/* Variables and functions */
 int SCIC_SDS_REMOTE_NODES_PER_DWORD ; 
 int SCU_STP_REMOTE_NODE_COUNT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sci_remote_node_table_set_group_index (struct sci_remote_node_table*,int,int) ; 
 int /*<<< orphan*/  sci_remote_node_table_set_node_index (struct sci_remote_node_table*,int) ; 

void sci_remote_node_table_initialize(
	struct sci_remote_node_table *remote_node_table,
	u32 remote_node_entries)
{
	u32 index;

	/*
	 * Initialize the raw data we could improve the speed by only initializing
	 * those entries that we are actually going to be used */
	memset(
		remote_node_table->available_remote_nodes,
		0x00,
		sizeof(remote_node_table->available_remote_nodes)
		);

	memset(
		remote_node_table->remote_node_groups,
		0x00,
		sizeof(remote_node_table->remote_node_groups)
		);

	/* Initialize the available remote node sets */
	remote_node_table->available_nodes_array_size = (u16)
							(remote_node_entries / SCIC_SDS_REMOTE_NODES_PER_DWORD)
							+ ((remote_node_entries % SCIC_SDS_REMOTE_NODES_PER_DWORD) != 0);


	/* Initialize each full DWORD to a FULL SET of remote nodes */
	for (index = 0; index < remote_node_entries; index++) {
		sci_remote_node_table_set_node_index(remote_node_table, index);
	}

	remote_node_table->group_array_size = (u16)
					      (remote_node_entries / (SCU_STP_REMOTE_NODE_COUNT * 32))
					      + ((remote_node_entries % (SCU_STP_REMOTE_NODE_COUNT * 32)) != 0);

	for (index = 0; index < (remote_node_entries / SCU_STP_REMOTE_NODE_COUNT); index++) {
		/*
		 * These are all guaranteed to be full slot values so fill them in the
		 * available sets of 3 remote nodes */
		sci_remote_node_table_set_group_index(remote_node_table, 2, index);
	}

	/* Now fill in any remainders that we may find */
	if ((remote_node_entries % SCU_STP_REMOTE_NODE_COUNT) == 2) {
		sci_remote_node_table_set_group_index(remote_node_table, 1, index);
	} else if ((remote_node_entries % SCU_STP_REMOTE_NODE_COUNT) == 1) {
		sci_remote_node_table_set_group_index(remote_node_table, 0, index);
	}
}