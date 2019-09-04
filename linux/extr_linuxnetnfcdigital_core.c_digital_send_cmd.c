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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nfc_digital_dev {int /*<<< orphan*/  cmd_work; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  cmd_queue; } ;
struct digital_tg_mdaa_params {int dummy; } ;
struct digital_cmd {int /*<<< orphan*/  queue; void* cb_context; int /*<<< orphan*/  cmd_cb; struct digital_tg_mdaa_params* mdaa_params; struct sk_buff* req; int /*<<< orphan*/  timeout; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  nfc_digital_cmd_complete_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct digital_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int digital_send_cmd(struct nfc_digital_dev *ddev, u8 cmd_type,
		     struct sk_buff *skb, struct digital_tg_mdaa_params *params,
		     u16 timeout, nfc_digital_cmd_complete_t cmd_cb,
		     void *cb_context)
{
	struct digital_cmd *cmd;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->type = cmd_type;
	cmd->timeout = timeout;
	cmd->req = skb;
	cmd->mdaa_params = params;
	cmd->cmd_cb = cmd_cb;
	cmd->cb_context = cb_context;
	INIT_LIST_HEAD(&cmd->queue);

	mutex_lock(&ddev->cmd_lock);
	list_add_tail(&cmd->queue, &ddev->cmd_queue);
	mutex_unlock(&ddev->cmd_lock);

	schedule_work(&ddev->cmd_work);

	return 0;
}