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
struct ath6kl_usb {int dummy; } ;
struct ath6kl {struct ath6kl_usb* hif_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_USB_CONTROL_REQ_RECV_BMI_RESP ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int ath6kl_usb_submit_ctrl_in (struct ath6kl_usb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_usb_bmi_read(struct ath6kl *ar, u8 *buf, u32 len)
{
	struct ath6kl_usb *ar_usb = ar->hif_priv;
	int ret;

	/* get response */
	ret = ath6kl_usb_submit_ctrl_in(ar_usb,
					ATH6KL_USB_CONTROL_REQ_RECV_BMI_RESP,
					0, 0, buf, len);
	if (ret) {
		ath6kl_err("Unable to read the bmi data from the device: %d\n",
			   ret);
		return ret;
	}

	return 0;
}