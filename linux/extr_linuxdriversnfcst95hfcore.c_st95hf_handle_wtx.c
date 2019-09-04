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
struct st95hf_context {TYPE_1__* nfcdev; struct nfc_digital_dev* ddev; } ;
struct param_list {int param_offset; int new_param_val; } ;
struct nfc_digital_dev {scalar_t__ curr_protocol; } ;
struct device {int dummy; } ;
struct TYPE_4__ {unsigned char* cmd_params; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 size_t CMD_ISO14443A_PROTOCOL_SELECT ; 
 size_t CMD_ISO14443B_PROTOCOL_SELECT ; 
 int /*<<< orphan*/  CMD_WTX_RESPONSE ; 
 scalar_t__ NFC_PROTO_ISO14443 ; 
 scalar_t__ NFC_PROTO_ISO14443_B ; 
 TYPE_2__* cmd_array ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int iso14443_config_fdt (struct st95hf_context*,unsigned char) ; 
 int st95hf_send_recv_cmd (struct st95hf_context*,int /*<<< orphan*/ ,int,struct param_list*,int) ; 

__attribute__((used)) static int st95hf_handle_wtx(struct st95hf_context *stcontext,
			     bool new_wtx,
			     int wtx_val)
{
	int result = 0;
	unsigned char val_mm = 0;
	struct param_list new_params[1];
	struct nfc_digital_dev *nfcddev = stcontext->ddev;
	struct device *dev = &stcontext->nfcdev->dev;

	if (new_wtx) {
		result = iso14443_config_fdt(stcontext, wtx_val & 0x3f);
		if (result) {
			dev_err(dev, "Config. setting error on WTX req, err = 0x%x\n",
				result);
			return result;
		}

		/* Send response of wtx with ASYNC as no response expected */
		new_params[0].param_offset = 1;
		new_params[0].new_param_val = wtx_val;

		result = st95hf_send_recv_cmd(stcontext,
					      CMD_WTX_RESPONSE,
					      1,
					      new_params,
					      false);
		if (result)
			dev_err(dev, "WTX response send, err = 0x%x\n", result);
		return result;
	}

	/* if no new wtx, cofigure with default values */
	if (nfcddev->curr_protocol == NFC_PROTO_ISO14443)
		val_mm = cmd_array[CMD_ISO14443A_PROTOCOL_SELECT].cmd_params[3];
	else if (nfcddev->curr_protocol == NFC_PROTO_ISO14443_B)
		val_mm = cmd_array[CMD_ISO14443B_PROTOCOL_SELECT].cmd_params[3];

	result = iso14443_config_fdt(stcontext, val_mm);
	if (result)
		dev_err(dev, "Default config. setting error after WTX processing, err = 0x%x\n",
			result);

	return result;
}