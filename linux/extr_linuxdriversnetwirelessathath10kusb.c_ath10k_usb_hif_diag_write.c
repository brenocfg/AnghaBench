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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_usb_ctrl_diag_cmd_write {int /*<<< orphan*/  value; void* address; void* cmd; } ;
struct ath10k_usb {scalar_t__ diag_cmd_buffer; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_USB_CONTROL_REQ_DIAG_CMD ; 
 int /*<<< orphan*/  ATH10K_USB_CTRL_DIAG_CC_WRITE ; 
 int EINVAL ; 
 int ath10k_usb_ctrl_msg_exchange (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ath10k_usb* ath10k_usb_priv (struct ath10k*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  memset (struct ath10k_usb_ctrl_diag_cmd_write*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath10k_usb_hif_diag_write(struct ath10k *ar, u32 address,
				     const void *data, int nbytes)
{
	struct ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	struct ath10k_usb_ctrl_diag_cmd_write *cmd;
	int ret;

	if (nbytes != sizeof(cmd->value))
		return -EINVAL;

	cmd = (struct ath10k_usb_ctrl_diag_cmd_write *)ar_usb->diag_cmd_buffer;
	memset(cmd, 0, sizeof(*cmd));
	cmd->cmd = cpu_to_le32(ATH10K_USB_CTRL_DIAG_CC_WRITE);
	cmd->address = cpu_to_le32(address);
	memcpy(&cmd->value, data, nbytes);

	ret = ath10k_usb_ctrl_msg_exchange(ar,
					   ATH10K_USB_CONTROL_REQ_DIAG_CMD,
					   (u8 *)cmd,
					   sizeof(*cmd),
					   0, NULL, NULL);
	if (ret)
		return ret;

	return 0;
}