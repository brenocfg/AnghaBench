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
struct lbs_private {int /*<<< orphan*/  cmdfreeq; } ;
struct cmd_ctrl_node {int /*<<< orphan*/  list; int /*<<< orphan*/  cmdbuf; scalar_t__ callback_arg; int /*<<< orphan*/ * callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_CMD_BUFFER_SIZE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __lbs_cleanup_and_insert_cmd(struct lbs_private *priv,
					 struct cmd_ctrl_node *cmdnode)
{
	if (!cmdnode)
		return;

	cmdnode->callback = NULL;
	cmdnode->callback_arg = 0;

	memset(cmdnode->cmdbuf, 0, LBS_CMD_BUFFER_SIZE);

	list_add_tail(&cmdnode->list, &priv->cmdfreeq);
}