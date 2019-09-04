#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;

/* Variables and functions */
 scalar_t__ BIT0 ; 
 scalar_t__ BIT6 ; 
 scalar_t__ BIT7 ; 
 int /*<<< orphan*/  CR6A ; 
 int IGA1 ; 
 int /*<<< orphan*/  SR1A ; 
 int /*<<< orphan*/  SR1B ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 TYPE_1__* palLUT_table ; 
 int /*<<< orphan*/  viafb_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  write_dac_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void viafb_init_dac(int set_iga)
{
	int i;
	u8 tmp;

	if (set_iga == IGA1) {
		/* access Primary Display's LUT */
		viafb_write_reg_mask(SR1A, VIASR, 0x00, BIT0);
		/* turn off LCK */
		viafb_write_reg_mask(SR1B, VIASR, 0x00, BIT7 + BIT6);
		for (i = 0; i < 256; i++) {
			write_dac_reg(i, palLUT_table[i].red,
				      palLUT_table[i].green,
				      palLUT_table[i].blue);
		}
		/* turn on LCK */
		viafb_write_reg_mask(SR1B, VIASR, 0xC0, BIT7 + BIT6);
	} else {
		tmp = viafb_read_reg(VIACR, CR6A);
		/* access Secondary Display's LUT */
		viafb_write_reg_mask(CR6A, VIACR, 0x40, BIT6);
		viafb_write_reg_mask(SR1A, VIASR, 0x01, BIT0);
		for (i = 0; i < 256; i++) {
			write_dac_reg(i, palLUT_table[i].red,
				      palLUT_table[i].green,
				      palLUT_table[i].blue);
		}
		/* set IGA1 DAC for default */
		viafb_write_reg_mask(SR1A, VIASR, 0x00, BIT0);
		viafb_write_reg(CR6A, VIACR, tmp);
	}
}