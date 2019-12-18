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
struct nci_dev {int dummy; } ;
struct nci_core_reset_cmd {int /*<<< orphan*/  reset_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_OP_CORE_RESET_CMD ; 
 int /*<<< orphan*/  NCI_RESET_TYPE_RESET_CONFIG ; 
 int /*<<< orphan*/  nci_send_cmd (struct nci_dev*,int /*<<< orphan*/ ,int,struct nci_core_reset_cmd*) ; 

__attribute__((used)) static void nci_reset_req(struct nci_dev *ndev, unsigned long opt)
{
	struct nci_core_reset_cmd cmd;

	cmd.reset_type = NCI_RESET_TYPE_RESET_CONFIG;
	nci_send_cmd(ndev, NCI_OP_CORE_RESET_CMD, 1, &cmd);
}