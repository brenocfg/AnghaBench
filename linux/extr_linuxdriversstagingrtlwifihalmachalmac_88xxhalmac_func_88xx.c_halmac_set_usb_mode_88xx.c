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
typedef  int u32 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_usb_mode { ____Placeholder_halmac_usb_mode } halmac_usb_mode ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT_APFM_OFFMAC ; 
 int /*<<< orphan*/  BIT_GET_USB23_SW_MODE_V1 (int) ; 
 int BIT_NO_PDN_CHIPOFF_V1 ; 
 int BIT_RSM_EN_V1 ; 
 int BIT_USB23_SW_MODE_V1 (int) ; 
 int BIT_USB3_USB2_TRANSITION ; 
 int HALMAC_REG_READ_16 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,scalar_t__) ; 
 int HALMAC_REG_READ_8 (struct halmac_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_16 (struct halmac_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int) ; 
 int HALMAC_RET_SUCCESS ; 
 int HALMAC_RET_USB2_3_SWITCH_UNSUPPORT ; 
 int HALMAC_RET_USB_MODE_UNCHANGE ; 
 int HALMAC_USB_MODE_U2 ; 
 int HALMAC_USB_MODE_U3 ; 
 scalar_t__ REG_PAD_CTRL2 ; 
 scalar_t__ REG_SYS_CFG2 ; 
 int /*<<< orphan*/  REG_SYS_PW_CTRL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

enum halmac_ret_status
halmac_set_usb_mode_88xx(struct halmac_adapter *halmac_adapter,
			 enum halmac_usb_mode usb_mode)
{
	u32 usb_temp;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;
	enum halmac_usb_mode current_usb_mode;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	current_usb_mode =
		HALMAC_REG_READ_8(halmac_adapter, REG_SYS_CFG2 + 3) == 0x20 ?
			HALMAC_USB_MODE_U3 :
			HALMAC_USB_MODE_U2;

	/*check if HW supports usb2_usb3 swtich*/
	usb_temp = HALMAC_REG_READ_32(halmac_adapter, REG_PAD_CTRL2);
	if (!BIT_GET_USB23_SW_MODE_V1(usb_temp) &&
	    !(usb_temp & BIT_USB3_USB2_TRANSITION)) {
		pr_err("HALMAC_HW_USB_MODE usb mode HW unsupport\n");
		return HALMAC_RET_USB2_3_SWITCH_UNSUPPORT;
	}

	if (usb_mode == current_usb_mode) {
		pr_err("HALMAC_HW_USB_MODE usb mode unchange\n");
		return HALMAC_RET_USB_MODE_UNCHANGE;
	}

	usb_temp &= ~(BIT_USB23_SW_MODE_V1(0x3));

	if (usb_mode == HALMAC_USB_MODE_U2) {
		/* usb3 to usb2 */
		HALMAC_REG_WRITE_32(
			halmac_adapter, REG_PAD_CTRL2,
			usb_temp | BIT_USB23_SW_MODE_V1(HALMAC_USB_MODE_U2) |
				BIT_RSM_EN_V1);
	} else {
		/* usb2 to usb3 */
		HALMAC_REG_WRITE_32(
			halmac_adapter, REG_PAD_CTRL2,
			usb_temp | BIT_USB23_SW_MODE_V1(HALMAC_USB_MODE_U3) |
				BIT_RSM_EN_V1);
	}

	HALMAC_REG_WRITE_8(halmac_adapter, REG_PAD_CTRL2 + 1,
			   4); /* set counter down timer 4x64 ms */
	HALMAC_REG_WRITE_16(
		halmac_adapter, REG_SYS_PW_CTRL,
		HALMAC_REG_READ_16(halmac_adapter, REG_SYS_PW_CTRL) |
			BIT_APFM_OFFMAC);
	usleep_range(1000, 1100);
	HALMAC_REG_WRITE_32(halmac_adapter, REG_PAD_CTRL2,
			    HALMAC_REG_READ_32(halmac_adapter, REG_PAD_CTRL2) |
				    BIT_NO_PDN_CHIPOFF_V1);

	return HALMAC_RET_SUCCESS;
}