#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* tmds_setting_info; TYPE_2__* chip_info; } ;
struct TYPE_5__ {int gfx_chip_name; } ;
struct TYPE_4__ {int h_active; int v_active; } ;

/* Variables and functions */
 scalar_t__ BIT0 ; 
 scalar_t__ BIT1 ; 
 scalar_t__ BIT2 ; 
 scalar_t__ BIT3 ; 
 scalar_t__ BIT4 ; 
 int /*<<< orphan*/  CR96 ; 
 int /*<<< orphan*/  SR1B ; 
 int /*<<< orphan*/  SR2A ; 
#define  UNICHROME_P4M890 129 
#define  UNICHROME_P4M900 128 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 TYPE_3__* viaparinfo ; 

__attribute__((used)) static void dvi_patch_skew_dvp0(void)
{
	/* Reset data driving first: */
	viafb_write_reg_mask(SR1B, VIASR, 0, BIT1);
	viafb_write_reg_mask(SR2A, VIASR, 0, BIT4);

	switch (viaparinfo->chip_info->gfx_chip_name) {
	case UNICHROME_P4M890:
		{
			if ((viaparinfo->tmds_setting_info->h_active == 1600) &&
				(viaparinfo->tmds_setting_info->v_active ==
				1200))
				viafb_write_reg_mask(CR96, VIACR, 0x03,
					       BIT0 + BIT1 + BIT2);
			else
				viafb_write_reg_mask(CR96, VIACR, 0x07,
					       BIT0 + BIT1 + BIT2);
			break;
		}

	case UNICHROME_P4M900:
		{
			viafb_write_reg_mask(CR96, VIACR, 0x07,
				       BIT0 + BIT1 + BIT2 + BIT3);
			viafb_write_reg_mask(SR1B, VIASR, 0x02, BIT1);
			viafb_write_reg_mask(SR2A, VIASR, 0x10, BIT4);
			break;
		}

	default:
		{
			break;
		}
	}
}