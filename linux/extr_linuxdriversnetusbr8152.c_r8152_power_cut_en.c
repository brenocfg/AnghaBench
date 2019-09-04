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
typedef  int /*<<< orphan*/  u32 ;
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_TYPE_USB ; 
 int /*<<< orphan*/  POWER_CUT ; 
 int /*<<< orphan*/  RESUME_INDICATE ; 
 int /*<<< orphan*/  USB_PM_CTRL_STATUS ; 
 int /*<<< orphan*/  USB_UPS_CTRL ; 
 int /*<<< orphan*/  ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8152_power_cut_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_UPS_CTRL);
	if (enable)
		ocp_data |= POWER_CUT;
	else
		ocp_data &= ~POWER_CUT;
	ocp_write_word(tp, MCU_TYPE_USB, USB_UPS_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_PM_CTRL_STATUS);
	ocp_data &= ~RESUME_INDICATE;
	ocp_write_word(tp, MCU_TYPE_USB, USB_PM_CTRL_STATUS, ocp_data);
}