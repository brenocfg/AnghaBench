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
struct nfc_target {scalar_t__ idx; int supported_protocols; int /*<<< orphan*/  logical_idx; } ;
struct nfc_dev {int dummy; } ;
struct nci_rf_discover_select_param {int /*<<< orphan*/  rf_protocol; int /*<<< orphan*/  rf_discovery_id; } ;
struct nci_dev {int target_active_prot; int n_targets; int /*<<< orphan*/  state; struct nfc_target* targets; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ NCI_POLL_ACTIVE ; 
 int /*<<< orphan*/  NCI_RF_DISC_SELECT_TIMEOUT ; 
 int /*<<< orphan*/  NCI_RF_PROTOCOL_ISO_DEP ; 
 int /*<<< orphan*/  NCI_RF_PROTOCOL_NFC_DEP ; 
 int /*<<< orphan*/  NCI_RF_PROTOCOL_T1T ; 
 int /*<<< orphan*/  NCI_RF_PROTOCOL_T2T ; 
 int /*<<< orphan*/  NCI_RF_PROTOCOL_T3T ; 
 scalar_t__ NCI_W4_HOST_SELECT ; 
 int NFC_PROTO_FELICA ; 
 int NFC_PROTO_ISO14443 ; 
 int NFC_PROTO_ISO14443_B ; 
 int NFC_PROTO_JEWEL ; 
 int NFC_PROTO_MIFARE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int nci_request (struct nci_dev*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_rf_discover_select_req ; 
 struct nci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int nci_activate_target(struct nfc_dev *nfc_dev,
			       struct nfc_target *target, __u32 protocol)
{
	struct nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	struct nci_rf_discover_select_param param;
	struct nfc_target *nci_target = NULL;
	int i;
	int rc = 0;

	pr_debug("target_idx %d, protocol 0x%x\n", target->idx, protocol);

	if ((atomic_read(&ndev->state) != NCI_W4_HOST_SELECT) &&
	    (atomic_read(&ndev->state) != NCI_POLL_ACTIVE)) {
		pr_err("there is no available target to activate\n");
		return -EINVAL;
	}

	if (ndev->target_active_prot) {
		pr_err("there is already an active target\n");
		return -EBUSY;
	}

	for (i = 0; i < ndev->n_targets; i++) {
		if (ndev->targets[i].idx == target->idx) {
			nci_target = &ndev->targets[i];
			break;
		}
	}

	if (!nci_target) {
		pr_err("unable to find the selected target\n");
		return -EINVAL;
	}

	if (!(nci_target->supported_protocols & (1 << protocol))) {
		pr_err("target does not support the requested protocol 0x%x\n",
		       protocol);
		return -EINVAL;
	}

	if (atomic_read(&ndev->state) == NCI_W4_HOST_SELECT) {
		param.rf_discovery_id = nci_target->logical_idx;

		if (protocol == NFC_PROTO_JEWEL)
			param.rf_protocol = NCI_RF_PROTOCOL_T1T;
		else if (protocol == NFC_PROTO_MIFARE)
			param.rf_protocol = NCI_RF_PROTOCOL_T2T;
		else if (protocol == NFC_PROTO_FELICA)
			param.rf_protocol = NCI_RF_PROTOCOL_T3T;
		else if (protocol == NFC_PROTO_ISO14443 ||
			 protocol == NFC_PROTO_ISO14443_B)
			param.rf_protocol = NCI_RF_PROTOCOL_ISO_DEP;
		else
			param.rf_protocol = NCI_RF_PROTOCOL_NFC_DEP;

		rc = nci_request(ndev, nci_rf_discover_select_req,
				 (unsigned long)&param,
				 msecs_to_jiffies(NCI_RF_DISC_SELECT_TIMEOUT));
	}

	if (!rc)
		ndev->target_active_prot = protocol;

	return rc;
}