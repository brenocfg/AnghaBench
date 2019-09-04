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
struct TYPE_4__ {TYPE_1__* chip_info; } ;
struct TYPE_3__ {int gfx_chip_name; } ;

/* Variables and functions */
 scalar_t__ BIT0 ; 
 scalar_t__ BIT1 ; 
 scalar_t__ BIT2 ; 
 scalar_t__ BIT3 ; 
 int /*<<< orphan*/  CR99 ; 
#define  UNICHROME_K8M890 130 
#define  UNICHROME_P4M890 129 
#define  UNICHROME_P4M900 128 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 TYPE_2__* viaparinfo ; 

__attribute__((used)) static void dvi_patch_skew_dvp_low(void)
{
	switch (viaparinfo->chip_info->gfx_chip_name) {
	case UNICHROME_K8M890:
		{
			viafb_write_reg_mask(CR99, VIACR, 0x03, BIT0 + BIT1);
			break;
		}

	case UNICHROME_P4M900:
		{
			viafb_write_reg_mask(CR99, VIACR, 0x08,
				       BIT0 + BIT1 + BIT2 + BIT3);
			break;
		}

	case UNICHROME_P4M890:
		{
			viafb_write_reg_mask(CR99, VIACR, 0x0F,
				       BIT0 + BIT1 + BIT2 + BIT3);
			break;
		}

	default:
		{
			break;
		}
	}
}