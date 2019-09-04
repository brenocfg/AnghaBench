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
typedef  size_t u32 ;
struct mwifiex_adapter {struct cmd_ctrl_node* cmd_pool; } ;
struct cmd_ctrl_node {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MWIFIEX_NUM_OF_CMD_BUFFER ; 
 int /*<<< orphan*/  MWIFIEX_SIZE_OF_CMD_BUFFER ; 
 int /*<<< orphan*/  dev_alloc_skb (int /*<<< orphan*/ ) ; 
 struct cmd_ctrl_node* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_insert_cmd_to_free_q (struct mwifiex_adapter*,struct cmd_ctrl_node*) ; 

int mwifiex_alloc_cmd_buffer(struct mwifiex_adapter *adapter)
{
	struct cmd_ctrl_node *cmd_array;
	u32 i;

	/* Allocate and initialize struct cmd_ctrl_node */
	cmd_array = kcalloc(MWIFIEX_NUM_OF_CMD_BUFFER,
			    sizeof(struct cmd_ctrl_node), GFP_KERNEL);
	if (!cmd_array)
		return -ENOMEM;

	adapter->cmd_pool = cmd_array;

	/* Allocate and initialize command buffers */
	for (i = 0; i < MWIFIEX_NUM_OF_CMD_BUFFER; i++) {
		cmd_array[i].skb = dev_alloc_skb(MWIFIEX_SIZE_OF_CMD_BUFFER);
		if (!cmd_array[i].skb) {
			mwifiex_dbg(adapter, ERROR,
				    "unable to allocate command buffer\n");
			return -ENOMEM;
		}
	}

	for (i = 0; i < MWIFIEX_NUM_OF_CMD_BUFFER; i++)
		mwifiex_insert_cmd_to_free_q(adapter, &cmd_array[i]);

	return 0;
}