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
struct nci_rf_discover_select_param {int rf_protocol; int /*<<< orphan*/  rf_discovery_id; } ;
struct nci_rf_discover_select_cmd {int rf_protocol; int /*<<< orphan*/  rf_interface; int /*<<< orphan*/  rf_discovery_id; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_OP_RF_DISCOVER_SELECT_CMD ; 
 int /*<<< orphan*/  NCI_RF_INTERFACE_FRAME ; 
 int /*<<< orphan*/  NCI_RF_INTERFACE_ISO_DEP ; 
 int /*<<< orphan*/  NCI_RF_INTERFACE_NFC_DEP ; 
#define  NCI_RF_PROTOCOL_ISO_DEP 129 
#define  NCI_RF_PROTOCOL_NFC_DEP 128 
 int /*<<< orphan*/  nci_send_cmd (struct nci_dev*,int /*<<< orphan*/ ,int,struct nci_rf_discover_select_cmd*) ; 

__attribute__((used)) static void nci_rf_discover_select_req(struct nci_dev *ndev, unsigned long opt)
{
	struct nci_rf_discover_select_param *param =
		(struct nci_rf_discover_select_param *)opt;
	struct nci_rf_discover_select_cmd cmd;

	cmd.rf_discovery_id = param->rf_discovery_id;
	cmd.rf_protocol = param->rf_protocol;

	switch (cmd.rf_protocol) {
	case NCI_RF_PROTOCOL_ISO_DEP:
		cmd.rf_interface = NCI_RF_INTERFACE_ISO_DEP;
		break;

	case NCI_RF_PROTOCOL_NFC_DEP:
		cmd.rf_interface = NCI_RF_INTERFACE_NFC_DEP;
		break;

	default:
		cmd.rf_interface = NCI_RF_INTERFACE_FRAME;
		break;
	}

	nci_send_cmd(ndev, NCI_OP_RF_DISCOVER_SELECT_CMD,
		     sizeof(struct nci_rf_discover_select_cmd), &cmd);
}