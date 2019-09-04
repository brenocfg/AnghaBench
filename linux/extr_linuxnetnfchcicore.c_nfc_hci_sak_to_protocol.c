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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */
 int NFC_HCI_TYPE_A_SEL_PROT (int /*<<< orphan*/ ) ; 
#define  NFC_HCI_TYPE_A_SEL_PROT_DEP 131 
#define  NFC_HCI_TYPE_A_SEL_PROT_ISO14443 130 
#define  NFC_HCI_TYPE_A_SEL_PROT_ISO14443_DEP 129 
#define  NFC_HCI_TYPE_A_SEL_PROT_MIFARE 128 
 int NFC_PROTO_ISO14443_MASK ; 
 int NFC_PROTO_MIFARE_MASK ; 
 int NFC_PROTO_NFC_DEP_MASK ; 

u32 nfc_hci_sak_to_protocol(u8 sak)
{
	switch (NFC_HCI_TYPE_A_SEL_PROT(sak)) {
	case NFC_HCI_TYPE_A_SEL_PROT_MIFARE:
		return NFC_PROTO_MIFARE_MASK;
	case NFC_HCI_TYPE_A_SEL_PROT_ISO14443:
		return NFC_PROTO_ISO14443_MASK;
	case NFC_HCI_TYPE_A_SEL_PROT_DEP:
		return NFC_PROTO_NFC_DEP_MASK;
	case NFC_HCI_TYPE_A_SEL_PROT_ISO14443_DEP:
		return NFC_PROTO_ISO14443_MASK | NFC_PROTO_NFC_DEP_MASK;
	default:
		return 0xffffffff;
	}
}