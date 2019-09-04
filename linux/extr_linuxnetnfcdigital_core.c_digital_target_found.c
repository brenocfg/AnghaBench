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
typedef  int u8 ;
struct nfc_target {int supported_protocols; } ;
struct nfc_digital_dev {size_t poll_tech_index; int curr_rf_tech; void (* skb_add_crc ) (struct sk_buff*) ;int (* skb_check_crc ) (struct sk_buff*) ;int poll_tech_count; int /*<<< orphan*/  nfc_dev; TYPE_1__* poll_techs; } ;
struct TYPE_2__ {int rf_tech; } ;

/* Variables and functions */
 scalar_t__ DIGITAL_DRV_CAPS_IN_CRC (struct nfc_digital_dev*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_FRAMING ; 
 int NFC_DIGITAL_FRAMING_ISO15693_T5T ; 
 int NFC_DIGITAL_FRAMING_NFCA_NFC_DEP ; 
 int NFC_DIGITAL_FRAMING_NFCA_T1T ; 
 int NFC_DIGITAL_FRAMING_NFCA_T2T ; 
 int NFC_DIGITAL_FRAMING_NFCA_T4T ; 
 int NFC_DIGITAL_FRAMING_NFCB_T4T ; 
 int NFC_DIGITAL_FRAMING_NFCF_NFC_DEP ; 
 int NFC_DIGITAL_FRAMING_NFCF_T3T ; 
 int NFC_DIGITAL_RF_TECH_106A ; 
#define  NFC_PROTO_FELICA 134 
#define  NFC_PROTO_ISO14443 133 
#define  NFC_PROTO_ISO14443_B 132 
#define  NFC_PROTO_ISO15693 131 
#define  NFC_PROTO_JEWEL 130 
#define  NFC_PROTO_MIFARE 129 
#define  NFC_PROTO_NFC_DEP 128 
 int digital_in_configure_hw (struct nfc_digital_dev*,int /*<<< orphan*/ ,int) ; 
 void digital_skb_add_crc_a (struct sk_buff*) ; 
 void digital_skb_add_crc_b (struct sk_buff*) ; 
 void digital_skb_add_crc_f (struct sk_buff*) ; 
 void digital_skb_add_crc_none (struct sk_buff*) ; 
 int digital_skb_check_crc_a (struct sk_buff*) ; 
 int digital_skb_check_crc_b (struct sk_buff*) ; 
 int digital_skb_check_crc_f (struct sk_buff*) ; 
 int digital_skb_check_crc_none (struct sk_buff*) ; 
 int nfc_targets_found (int /*<<< orphan*/ ,struct nfc_target*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int digital_target_found(struct nfc_digital_dev *ddev,
			 struct nfc_target *target, u8 protocol)
{
	int rc;
	u8 framing;
	u8 rf_tech;
	u8 poll_tech_count;
	int (*check_crc)(struct sk_buff *skb);
	void (*add_crc)(struct sk_buff *skb);

	rf_tech = ddev->poll_techs[ddev->poll_tech_index].rf_tech;

	switch (protocol) {
	case NFC_PROTO_JEWEL:
		framing = NFC_DIGITAL_FRAMING_NFCA_T1T;
		check_crc = digital_skb_check_crc_b;
		add_crc = digital_skb_add_crc_b;
		break;

	case NFC_PROTO_MIFARE:
		framing = NFC_DIGITAL_FRAMING_NFCA_T2T;
		check_crc = digital_skb_check_crc_a;
		add_crc = digital_skb_add_crc_a;
		break;

	case NFC_PROTO_FELICA:
		framing = NFC_DIGITAL_FRAMING_NFCF_T3T;
		check_crc = digital_skb_check_crc_f;
		add_crc = digital_skb_add_crc_f;
		break;

	case NFC_PROTO_NFC_DEP:
		if (rf_tech == NFC_DIGITAL_RF_TECH_106A) {
			framing = NFC_DIGITAL_FRAMING_NFCA_NFC_DEP;
			check_crc = digital_skb_check_crc_a;
			add_crc = digital_skb_add_crc_a;
		} else {
			framing = NFC_DIGITAL_FRAMING_NFCF_NFC_DEP;
			check_crc = digital_skb_check_crc_f;
			add_crc = digital_skb_add_crc_f;
		}
		break;

	case NFC_PROTO_ISO15693:
		framing = NFC_DIGITAL_FRAMING_ISO15693_T5T;
		check_crc = digital_skb_check_crc_b;
		add_crc = digital_skb_add_crc_b;
		break;

	case NFC_PROTO_ISO14443:
		framing = NFC_DIGITAL_FRAMING_NFCA_T4T;
		check_crc = digital_skb_check_crc_a;
		add_crc = digital_skb_add_crc_a;
		break;

	case NFC_PROTO_ISO14443_B:
		framing = NFC_DIGITAL_FRAMING_NFCB_T4T;
		check_crc = digital_skb_check_crc_b;
		add_crc = digital_skb_add_crc_b;
		break;

	default:
		pr_err("Invalid protocol %d\n", protocol);
		return -EINVAL;
	}

	pr_debug("rf_tech=%d, protocol=%d\n", rf_tech, protocol);

	ddev->curr_rf_tech = rf_tech;

	if (DIGITAL_DRV_CAPS_IN_CRC(ddev)) {
		ddev->skb_add_crc = digital_skb_add_crc_none;
		ddev->skb_check_crc = digital_skb_check_crc_none;
	} else {
		ddev->skb_add_crc = add_crc;
		ddev->skb_check_crc = check_crc;
	}

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING, framing);
	if (rc)
		return rc;

	target->supported_protocols = (1 << protocol);

	poll_tech_count = ddev->poll_tech_count;
	ddev->poll_tech_count = 0;

	rc = nfc_targets_found(ddev->nfc_dev, target, 1);
	if (rc) {
		ddev->poll_tech_count = poll_tech_count;
		return rc;
	}

	return 0;
}