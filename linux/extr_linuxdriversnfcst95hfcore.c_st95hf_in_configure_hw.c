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
struct st95hf_context {int /*<<< orphan*/  sendrcv_trflag; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int NFC_DIGITAL_CONFIG_FRAMING ; 
 int NFC_DIGITAL_CONFIG_RF_TECH ; 
#define  NFC_DIGITAL_FRAMING_ISO15693_INVENTORY 135 
#define  NFC_DIGITAL_FRAMING_ISO15693_T5T 134 
#define  NFC_DIGITAL_FRAMING_NFCA_NFC_DEP 133 
#define  NFC_DIGITAL_FRAMING_NFCA_SHORT 132 
#define  NFC_DIGITAL_FRAMING_NFCA_STANDARD 131 
#define  NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A 130 
#define  NFC_DIGITAL_FRAMING_NFCA_T4T 129 
#define  NFC_DIGITAL_FRAMING_NFCB 128 
 int /*<<< orphan*/  TRFLAG_NFCA_SHORT_FRAME ; 
 int /*<<< orphan*/  TRFLAG_NFCA_STD_FRAME ; 
 int /*<<< orphan*/  TRFLAG_NFCA_STD_FRAME_CRC ; 
 struct st95hf_context* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 
 int st95hf_select_protocol (struct st95hf_context*,int) ; 

__attribute__((used)) static int st95hf_in_configure_hw(struct nfc_digital_dev *ddev,
				  int type,
				  int param)
{
	struct st95hf_context *stcontext = nfc_digital_get_drvdata(ddev);

	if (type == NFC_DIGITAL_CONFIG_RF_TECH)
		return st95hf_select_protocol(stcontext, param);

	if (type == NFC_DIGITAL_CONFIG_FRAMING) {
		switch (param) {
		case NFC_DIGITAL_FRAMING_NFCA_SHORT:
			stcontext->sendrcv_trflag = TRFLAG_NFCA_SHORT_FRAME;
			break;
		case NFC_DIGITAL_FRAMING_NFCA_STANDARD:
			stcontext->sendrcv_trflag = TRFLAG_NFCA_STD_FRAME;
			break;
		case NFC_DIGITAL_FRAMING_NFCA_T4T:
		case NFC_DIGITAL_FRAMING_NFCA_NFC_DEP:
		case NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A:
			stcontext->sendrcv_trflag = TRFLAG_NFCA_STD_FRAME_CRC;
			break;
		case NFC_DIGITAL_FRAMING_NFCB:
		case NFC_DIGITAL_FRAMING_ISO15693_INVENTORY:
		case NFC_DIGITAL_FRAMING_ISO15693_T5T:
			break;
		}
	}

	return 0;
}