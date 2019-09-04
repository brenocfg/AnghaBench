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
struct lbs_private {struct cmd_ctrl_node* cmd_array; } ;
struct cmd_ctrl_node {struct cmd_ctrl_node* cmdbuf; } ;

/* Variables and functions */
 unsigned int LBS_NUM_CMD_BUFFERS ; 
 int /*<<< orphan*/  kfree (struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  lbs_deb_host (char*) ; 

int lbs_free_cmd_buffer(struct lbs_private *priv)
{
	struct cmd_ctrl_node *cmdarray;
	unsigned int i;

	/* need to check if cmd array is allocated or not */
	if (priv->cmd_array == NULL) {
		lbs_deb_host("FREE_CMD_BUF: cmd_array is NULL\n");
		goto done;
	}

	cmdarray = priv->cmd_array;

	/* Release shared memory buffers */
	for (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) {
		if (cmdarray[i].cmdbuf) {
			kfree(cmdarray[i].cmdbuf);
			cmdarray[i].cmdbuf = NULL;
		}
	}

	/* Release cmd_ctrl_node */
	if (priv->cmd_array) {
		kfree(priv->cmd_array);
		priv->cmd_array = NULL;
	}

done:
	return 0;
}