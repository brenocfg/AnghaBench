#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st95_digital_cmd_complete_arg {int rats; } ;
struct st95hf_context {int fwi; int current_rf_tech; int /*<<< orphan*/  sendrcv_trflag; struct st95_digital_cmd_complete_arg complete_cb_arg; TYPE_1__* nfcdev; struct nfc_digital_dev* ddev; } ;
struct sk_buff {int len; int* data; } ;
struct nfc_digital_dev {scalar_t__ curr_protocol; } ;
struct device {int dummy; } ;
struct TYPE_4__ {unsigned char* cmd_params; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 size_t CMD_ISO14443A_PROTOCOL_SELECT ; 
#define  NFC_DIGITAL_RF_TECH_106A 130 
#define  NFC_DIGITAL_RF_TECH_106B 129 
#define  NFC_DIGITAL_RF_TECH_ISO15693 128 
 scalar_t__ NFC_PROTO_ISO14443 ; 
 int RATS_TA1_PRESENT_MASK ; 
 int RATS_TB1_PRESENT_MASK ; 
 int TB1_FWI_MASK ; 
 int /*<<< orphan*/  TRFLAG_NFCA_STD_FRAME_CRC ; 
 TYPE_2__* cmd_array ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int iso14443_config_fdt (struct st95hf_context*,unsigned char) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int st95hf_response_handler(struct st95hf_context *stcontext,
				   struct sk_buff *skb_resp,
				   int res_len)
{
	int result = 0;
	int skb_len;
	unsigned char val_mm;
	struct nfc_digital_dev *nfcddev = stcontext->ddev;
	struct device *dev = &stcontext->nfcdev->dev;
	struct st95_digital_cmd_complete_arg *cb_arg;

	cb_arg = &stcontext->complete_cb_arg;

	/* Process the response */
	skb_put(skb_resp, res_len);

	/* Remove st95 header */
	skb_pull(skb_resp, 2);

	skb_len = skb_resp->len;

	/* check if it is case of RATS request reply & FWI is present */
	if (nfcddev->curr_protocol == NFC_PROTO_ISO14443 && cb_arg->rats &&
	    (skb_resp->data[1] & RATS_TB1_PRESENT_MASK)) {
		if (skb_resp->data[1] & RATS_TA1_PRESENT_MASK)
			stcontext->fwi =
				(skb_resp->data[3] & TB1_FWI_MASK) >> 4;
		else
			stcontext->fwi =
				(skb_resp->data[2] & TB1_FWI_MASK) >> 4;

		val_mm = cmd_array[CMD_ISO14443A_PROTOCOL_SELECT].cmd_params[3];

		result = iso14443_config_fdt(stcontext, val_mm);
		if (result) {
			dev_err(dev, "error in config_fdt to handle fwi of ATS, error=%d\n",
				result);
			return result;
		}
	}
	cb_arg->rats = false;

	/* Remove CRC bytes only if received frames data has an eod (CRC) */
	switch (stcontext->current_rf_tech) {
	case NFC_DIGITAL_RF_TECH_106A:
		if (stcontext->sendrcv_trflag == TRFLAG_NFCA_STD_FRAME_CRC)
			skb_trim(skb_resp, (skb_len - 5));
		else
			skb_trim(skb_resp, (skb_len - 3));
		break;
	case NFC_DIGITAL_RF_TECH_106B:
	case NFC_DIGITAL_RF_TECH_ISO15693:
		skb_trim(skb_resp, (skb_len - 3));
		break;
	}

	return result;
}