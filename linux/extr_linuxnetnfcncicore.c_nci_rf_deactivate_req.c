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
struct nci_rf_deactivate_cmd {unsigned long type; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_OP_RF_DEACTIVATE_CMD ; 
 int /*<<< orphan*/  nci_send_cmd (struct nci_dev*,int /*<<< orphan*/ ,int,struct nci_rf_deactivate_cmd*) ; 

__attribute__((used)) static void nci_rf_deactivate_req(struct nci_dev *ndev, unsigned long opt)
{
	struct nci_rf_deactivate_cmd cmd;

	cmd.type = opt;

	nci_send_cmd(ndev, NCI_OP_RF_DEACTIVATE_CMD,
		     sizeof(struct nci_rf_deactivate_cmd), &cmd);
}