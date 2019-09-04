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
struct mgmt_pending_cmd {int /*<<< orphan*/  (* cmd_complete ) (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sk; struct mgmt_cp_unpair_device* param; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_cp_unpair_device {TYPE_1__ addr; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unpaired (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  stub1 (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unpair_device_rsp(struct mgmt_pending_cmd *cmd, void *data)
{
	struct hci_dev *hdev = data;
	struct mgmt_cp_unpair_device *cp = cmd->param;

	device_unpaired(hdev, &cp->addr.bdaddr, cp->addr.type, cmd->sk);

	cmd->cmd_complete(cmd, 0);
	mgmt_pending_remove(cmd);
}