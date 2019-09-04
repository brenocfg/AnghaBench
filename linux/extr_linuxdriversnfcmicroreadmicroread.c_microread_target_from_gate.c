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
struct nfc_target {int /*<<< orphan*/  supported_protocols; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
#define  MICROREAD_GATE_ID_P2P_INITIATOR 128 
 int /*<<< orphan*/  NFC_PROTO_NFC_DEP_MASK ; 

__attribute__((used)) static int microread_target_from_gate(struct nfc_hci_dev *hdev, u8 gate,
				      struct nfc_target *target)
{
	switch (gate) {
	case MICROREAD_GATE_ID_P2P_INITIATOR:
		target->supported_protocols = NFC_PROTO_NFC_DEP_MASK;
		break;
	default:
		return -EPROTO;
	}

	return 0;
}