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
struct rf_tech_specific_params_nfcv_poll {int /*<<< orphan*/  uid; int /*<<< orphan*/  dsfid; } ;
struct rf_tech_specific_params_nfcf_poll {int /*<<< orphan*/  sensf_res; int /*<<< orphan*/  sensf_res_len; } ;
struct rf_tech_specific_params_nfcb_poll {int /*<<< orphan*/  sensb_res; int /*<<< orphan*/  sensb_res_len; } ;
struct rf_tech_specific_params_nfca_poll {int /*<<< orphan*/  nfcid1; int /*<<< orphan*/  nfcid1_len; int /*<<< orphan*/  sel_res; int /*<<< orphan*/  sens_res; } ;
struct nfc_target {int is_iso15693; int supported_protocols; int /*<<< orphan*/  iso15693_uid; int /*<<< orphan*/  iso15693_dsfid; int /*<<< orphan*/  sensf_res_len; int /*<<< orphan*/  sensf_res; int /*<<< orphan*/  sensb_res_len; int /*<<< orphan*/  sensb_res; int /*<<< orphan*/  nfcid1_len; int /*<<< orphan*/  nfcid1; int /*<<< orphan*/  sel_res; int /*<<< orphan*/  sens_res; } ;
struct nci_dev {int poll_prots; } ;
typedef  scalar_t__ __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int EPROTO ; 
 scalar_t__ NCI_NFC_A_PASSIVE_POLL_MODE ; 
 scalar_t__ NCI_NFC_B_PASSIVE_POLL_MODE ; 
 scalar_t__ NCI_NFC_F_PASSIVE_POLL_MODE ; 
 scalar_t__ NCI_NFC_V_PASSIVE_POLL_MODE ; 
 scalar_t__ NCI_RF_PROTOCOL_ISO_DEP ; 
 scalar_t__ NCI_RF_PROTOCOL_NFC_DEP ; 
 scalar_t__ NCI_RF_PROTOCOL_T1T ; 
 scalar_t__ NCI_RF_PROTOCOL_T2T ; 
 scalar_t__ NCI_RF_PROTOCOL_T3T ; 
 scalar_t__ NCI_RF_PROTOCOL_T5T ; 
 int /*<<< orphan*/  NFC_ISO15693_UID_MAXSIZE ; 
 int NFC_PROTO_FELICA_MASK ; 
 int NFC_PROTO_ISO14443_B_MASK ; 
 int NFC_PROTO_ISO14443_MASK ; 
 int NFC_PROTO_ISO15693_MASK ; 
 int NFC_PROTO_JEWEL_MASK ; 
 int NFC_PROTO_MIFARE_MASK ; 
 int NFC_PROTO_NFC_DEP_MASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nci_get_prop_rf_protocol (struct nci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int nci_add_new_protocol(struct nci_dev *ndev,
				struct nfc_target *target,
				__u8 rf_protocol,
				__u8 rf_tech_and_mode,
				void *params)
{
	struct rf_tech_specific_params_nfca_poll *nfca_poll;
	struct rf_tech_specific_params_nfcb_poll *nfcb_poll;
	struct rf_tech_specific_params_nfcf_poll *nfcf_poll;
	struct rf_tech_specific_params_nfcv_poll *nfcv_poll;
	__u32 protocol;

	if (rf_protocol == NCI_RF_PROTOCOL_T1T)
		protocol = NFC_PROTO_JEWEL_MASK;
	else if (rf_protocol == NCI_RF_PROTOCOL_T2T)
		protocol = NFC_PROTO_MIFARE_MASK;
	else if (rf_protocol == NCI_RF_PROTOCOL_ISO_DEP)
		if (rf_tech_and_mode == NCI_NFC_A_PASSIVE_POLL_MODE)
			protocol = NFC_PROTO_ISO14443_MASK;
		else
			protocol = NFC_PROTO_ISO14443_B_MASK;
	else if (rf_protocol == NCI_RF_PROTOCOL_T3T)
		protocol = NFC_PROTO_FELICA_MASK;
	else if (rf_protocol == NCI_RF_PROTOCOL_NFC_DEP)
		protocol = NFC_PROTO_NFC_DEP_MASK;
	else if (rf_protocol == NCI_RF_PROTOCOL_T5T)
		protocol = NFC_PROTO_ISO15693_MASK;
	else
		protocol = nci_get_prop_rf_protocol(ndev, rf_protocol);

	if (!(protocol & ndev->poll_prots)) {
		pr_err("the target found does not have the desired protocol\n");
		return -EPROTO;
	}

	if (rf_tech_and_mode == NCI_NFC_A_PASSIVE_POLL_MODE) {
		nfca_poll = (struct rf_tech_specific_params_nfca_poll *)params;

		target->sens_res = nfca_poll->sens_res;
		target->sel_res = nfca_poll->sel_res;
		target->nfcid1_len = nfca_poll->nfcid1_len;
		if (target->nfcid1_len > 0) {
			memcpy(target->nfcid1, nfca_poll->nfcid1,
			       target->nfcid1_len);
		}
	} else if (rf_tech_and_mode == NCI_NFC_B_PASSIVE_POLL_MODE) {
		nfcb_poll = (struct rf_tech_specific_params_nfcb_poll *)params;

		target->sensb_res_len = nfcb_poll->sensb_res_len;
		if (target->sensb_res_len > 0) {
			memcpy(target->sensb_res, nfcb_poll->sensb_res,
			       target->sensb_res_len);
		}
	} else if (rf_tech_and_mode == NCI_NFC_F_PASSIVE_POLL_MODE) {
		nfcf_poll = (struct rf_tech_specific_params_nfcf_poll *)params;

		target->sensf_res_len = nfcf_poll->sensf_res_len;
		if (target->sensf_res_len > 0) {
			memcpy(target->sensf_res, nfcf_poll->sensf_res,
			       target->sensf_res_len);
		}
	} else if (rf_tech_and_mode == NCI_NFC_V_PASSIVE_POLL_MODE) {
		nfcv_poll = (struct rf_tech_specific_params_nfcv_poll *)params;

		target->is_iso15693 = 1;
		target->iso15693_dsfid = nfcv_poll->dsfid;
		memcpy(target->iso15693_uid, nfcv_poll->uid, NFC_ISO15693_UID_MAXSIZE);
	} else {
		pr_err("unsupported rf_tech_and_mode 0x%x\n", rf_tech_and_mode);
		return -EPROTO;
	}

	target->supported_protocols |= protocol;

	pr_debug("protocol 0x%x\n", protocol);

	return 0;
}