#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nci_set_config_param {scalar_t__ len; int /*<<< orphan*/  val; int /*<<< orphan*/  id; } ;
struct nci_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  val; int /*<<< orphan*/  id; } ;
struct nci_core_set_config_cmd {int num_params; TYPE_1__ param; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NCI_MAX_PARAM_LEN ; 
 int /*<<< orphan*/  NCI_OP_CORE_SET_CONFIG_CMD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nci_send_cmd (struct nci_dev*,int /*<<< orphan*/ ,scalar_t__,struct nci_core_set_config_cmd*) ; 

__attribute__((used)) static void nci_set_config_req(struct nci_dev *ndev, unsigned long opt)
{
	struct nci_set_config_param *param = (struct nci_set_config_param *)opt;
	struct nci_core_set_config_cmd cmd;

	BUG_ON(param->len > NCI_MAX_PARAM_LEN);

	cmd.num_params = 1;
	cmd.param.id = param->id;
	cmd.param.len = param->len;
	memcpy(cmd.param.val, param->val, param->len);

	nci_send_cmd(ndev, NCI_OP_CORE_SET_CONFIG_CMD, (3 + param->len), &cmd);
}