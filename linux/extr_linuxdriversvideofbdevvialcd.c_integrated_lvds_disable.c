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
struct lvds_setting_information {int dummy; } ;
struct lvds_chip_information {int output_interface; } ;

/* Variables and functions */
 scalar_t__ BIT1 ; 
 scalar_t__ BIT3 ; 
 scalar_t__ BIT6 ; 
 scalar_t__ BIT7 ; 
 int /*<<< orphan*/  CR6A ; 
 int /*<<< orphan*/  CR91 ; 
 int /*<<< orphan*/  CRD2 ; 
 int /*<<< orphan*/  CRD3 ; 
 int /*<<< orphan*/  CRD4 ; 
#define  INTERFACE_LVDS0 130 
#define  INTERFACE_LVDS0LVDS1 129 
#define  INTERFACE_LVDS1 128 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void integrated_lvds_disable(struct lvds_setting_information
			     *plvds_setting_info,
			     struct lvds_chip_information *plvds_chip_info)
{
	bool turn_off_first_powersequence = false;
	bool turn_off_second_powersequence = false;
	if (INTERFACE_LVDS0LVDS1 == plvds_chip_info->output_interface)
		turn_off_first_powersequence = true;
	if (INTERFACE_LVDS0 == plvds_chip_info->output_interface)
		turn_off_first_powersequence = true;
	if (INTERFACE_LVDS1 == plvds_chip_info->output_interface)
		turn_off_second_powersequence = true;
	if (turn_off_second_powersequence) {
		/* Use second power sequence control: */

		/* Turn off power sequence. */
		viafb_write_reg_mask(CRD4, VIACR, 0, BIT1);

		/* Turn off back light. */
		viafb_write_reg_mask(CRD3, VIACR, 0xC0, BIT6 + BIT7);
	}
	if (turn_off_first_powersequence) {
		/* Use first power sequence control: */

		/* Turn off power sequence. */
		viafb_write_reg_mask(CR6A, VIACR, 0, BIT3);

		/* Turn off back light. */
		viafb_write_reg_mask(CR91, VIACR, 0xC0, BIT6 + BIT7);
	}

	/* Power off LVDS channel. */
	switch (plvds_chip_info->output_interface) {
	case INTERFACE_LVDS0:
		{
			viafb_write_reg_mask(CRD2, VIACR, 0x80, BIT7);
			break;
		}

	case INTERFACE_LVDS1:
		{
			viafb_write_reg_mask(CRD2, VIACR, 0x40, BIT6);
			break;
		}

	case INTERFACE_LVDS0LVDS1:
		{
			viafb_write_reg_mask(CRD2, VIACR, 0xC0, BIT6 + BIT7);
			break;
		}
	}
}