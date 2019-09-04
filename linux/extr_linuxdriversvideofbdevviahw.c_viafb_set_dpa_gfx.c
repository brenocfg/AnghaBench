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
struct GFX_DPA_SETTING {int /*<<< orphan*/  DFPLow; int /*<<< orphan*/  DFPHigh; int /*<<< orphan*/  DVP1Driving; int /*<<< orphan*/  DVP1; int /*<<< orphan*/  DVP0DataDri_S1; int /*<<< orphan*/  DVP0DataDri_S; int /*<<< orphan*/  DVP0ClockDri_S1; int /*<<< orphan*/  DVP0ClockDri_S; int /*<<< orphan*/  DVP0; } ;

/* Variables and functions */
 int BIT1 ; 
 int BIT2 ; 
 int BIT4 ; 
 int BIT5 ; 
 int /*<<< orphan*/  CR96 ; 
 int /*<<< orphan*/  CR97 ; 
 int /*<<< orphan*/  CR99 ; 
 int /*<<< orphan*/  CR9B ; 
#define  INTERFACE_DFP 132 
#define  INTERFACE_DFP_HIGH 131 
#define  INTERFACE_DFP_LOW 130 
#define  INTERFACE_DVP0 129 
#define  INTERFACE_DVP1 128 
 int /*<<< orphan*/  SR1B ; 
 int /*<<< orphan*/  SR1E ; 
 int /*<<< orphan*/  SR2A ; 
 int /*<<< orphan*/  SR65 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void viafb_set_dpa_gfx(int output_interface, struct GFX_DPA_SETTING\
					*p_gfx_dpa_setting)
{
	switch (output_interface) {
	case INTERFACE_DVP0:
		{
			/* DVP0 Clock Polarity and Adjust: */
			viafb_write_reg_mask(CR96, VIACR,
				       p_gfx_dpa_setting->DVP0, 0x0F);

			/* DVP0 Clock and Data Pads Driving: */
			viafb_write_reg_mask(SR1E, VIASR,
				       p_gfx_dpa_setting->DVP0ClockDri_S, BIT2);
			viafb_write_reg_mask(SR2A, VIASR,
				       p_gfx_dpa_setting->DVP0ClockDri_S1,
				       BIT4);
			viafb_write_reg_mask(SR1B, VIASR,
				       p_gfx_dpa_setting->DVP0DataDri_S, BIT1);
			viafb_write_reg_mask(SR2A, VIASR,
				       p_gfx_dpa_setting->DVP0DataDri_S1, BIT5);
			break;
		}

	case INTERFACE_DVP1:
		{
			/* DVP1 Clock Polarity and Adjust: */
			viafb_write_reg_mask(CR9B, VIACR,
				       p_gfx_dpa_setting->DVP1, 0x0F);

			/* DVP1 Clock and Data Pads Driving: */
			viafb_write_reg_mask(SR65, VIASR,
				       p_gfx_dpa_setting->DVP1Driving, 0x0F);
			break;
		}

	case INTERFACE_DFP_HIGH:
		{
			viafb_write_reg_mask(CR97, VIACR,
				       p_gfx_dpa_setting->DFPHigh, 0x0F);
			break;
		}

	case INTERFACE_DFP_LOW:
		{
			viafb_write_reg_mask(CR99, VIACR,
				       p_gfx_dpa_setting->DFPLow, 0x0F);
			break;
		}

	case INTERFACE_DFP:
		{
			viafb_write_reg_mask(CR97, VIACR,
				       p_gfx_dpa_setting->DFPHigh, 0x0F);
			viafb_write_reg_mask(CR99, VIACR,
				       p_gfx_dpa_setting->DFPLow, 0x0F);
			break;
		}
	}
}