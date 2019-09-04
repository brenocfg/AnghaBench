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
typedef  int u8 ;
struct nfc_target {int sens_res; int /*<<< orphan*/  supported_protocols; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  NFC_PROTO_FELICA_MASK ; 
 int /*<<< orphan*/  NFC_PROTO_JEWEL_MASK ; 
 int /*<<< orphan*/  NFC_PROTO_NFC_DEP_MASK ; 
#define  PN544_RF_READER_F_GATE 130 
#define  PN544_RF_READER_JEWEL_GATE 129 
#define  PN544_RF_READER_NFCIP1_INITIATOR_GATE 128 

__attribute__((used)) static int pn544_hci_target_from_gate(struct nfc_hci_dev *hdev, u8 gate,
				      struct nfc_target *target)
{
	switch (gate) {
	case PN544_RF_READER_F_GATE:
		target->supported_protocols = NFC_PROTO_FELICA_MASK;
		break;
	case PN544_RF_READER_JEWEL_GATE:
		target->supported_protocols = NFC_PROTO_JEWEL_MASK;
		target->sens_res = 0x0c00;
		break;
	case PN544_RF_READER_NFCIP1_INITIATOR_GATE:
		target->supported_protocols = NFC_PROTO_NFC_DEP_MASK;
		break;
	default:
		return -EPROTO;
	}

	return 0;
}