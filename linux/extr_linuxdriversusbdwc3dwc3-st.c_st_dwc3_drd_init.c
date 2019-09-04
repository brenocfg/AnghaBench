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
struct st_dwc3 {int dr_mode; int /*<<< orphan*/  syscfg_reg_off; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int USB3_CONTROL_MASK ; 
 int USB3_DELAY_VBUSVALID ; 
 int USB3_DEVICE_NOT_HOST ; 
 int USB3_FORCE_DMPULLDOWN2 ; 
 int USB3_FORCE_DPPULLDOWN2 ; 
 int USB3_FORCE_OPMODE (int) ; 
 int USB3_FORCE_VBUSVALID ; 
 int USB3_SEL_FORCE_DMPULLDOWN2 ; 
 int USB3_SEL_FORCE_DPPULLDOWN2 ; 
 int USB3_SEL_FORCE_OPMODE ; 
#define  USB_DR_MODE_HOST 129 
#define  USB_DR_MODE_PERIPHERAL 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int st_dwc3_drd_init(struct st_dwc3 *dwc3_data)
{
	u32 val;
	int err;

	err = regmap_read(dwc3_data->regmap, dwc3_data->syscfg_reg_off, &val);
	if (err)
		return err;

	val &= USB3_CONTROL_MASK;

	switch (dwc3_data->dr_mode) {
	case USB_DR_MODE_PERIPHERAL:

		val &= ~(USB3_DELAY_VBUSVALID
			| USB3_SEL_FORCE_OPMODE | USB3_FORCE_OPMODE(0x3)
			| USB3_SEL_FORCE_DPPULLDOWN2 | USB3_FORCE_DPPULLDOWN2
			| USB3_SEL_FORCE_DMPULLDOWN2 | USB3_FORCE_DMPULLDOWN2);

		/*
		 * USB3_PORT2_FORCE_VBUSVALID When '1' and when
		 * USB3_PORT2_DEVICE_NOT_HOST = 1, forces VBUSVLDEXT2 input
		 * of the pico PHY to 1.
		 */

		val |= USB3_DEVICE_NOT_HOST | USB3_FORCE_VBUSVALID;
		break;

	case USB_DR_MODE_HOST:

		val &= ~(USB3_DEVICE_NOT_HOST | USB3_FORCE_VBUSVALID
			| USB3_SEL_FORCE_OPMODE	| USB3_FORCE_OPMODE(0x3)
			| USB3_SEL_FORCE_DPPULLDOWN2 | USB3_FORCE_DPPULLDOWN2
			| USB3_SEL_FORCE_DMPULLDOWN2 | USB3_FORCE_DMPULLDOWN2);

		/*
		 * USB3_DELAY_VBUSVALID is ANDed with USB_C_VBUSVALID. Thus,
		 * when set to ‘0‘, it can delay the arrival of VBUSVALID
		 * information to VBUSVLDEXT2 input of the pico PHY.
		 * We don't want to do that so we set the bit to '1'.
		 */

		val |= USB3_DELAY_VBUSVALID;
		break;

	default:
		dev_err(dwc3_data->dev, "Unsupported mode of operation %d\n",
			dwc3_data->dr_mode);
		return -EINVAL;
	}

	return regmap_write(dwc3_data->regmap, dwc3_data->syscfg_reg_off, val);
}