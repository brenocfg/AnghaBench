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
typedef  int u16 ;
struct hw {int dummy; } ;

/* Variables and functions */
#define  ADC_AUX 132 
#define  ADC_LINEIN 131 
#define  ADC_MICIN 130 
#define  ADC_NONE 129 
#define  ADC_VIDEO 128 
 int /*<<< orphan*/  GPIO ; 
 int /*<<< orphan*/  ID0 ; 
 int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 unsigned int hw_read_pci (struct hw*,int) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_write_pci (struct hw*,int,int) ; 
 int /*<<< orphan*/  i2c_lock (struct hw*) ; 
 scalar_t__ i2c_unlock (struct hw*) ; 
 int /*<<< orphan*/  i2c_write (struct hw*,int,int,int) ; 

__attribute__((used)) static int adc_init_SBx(struct hw *hw, int input, int mic20db)
{
	u16 gpioorg;
	u16 input_source;
	u32 adcdata;
	unsigned int ret;

	input_source = 0x100;  /* default to analog */
	switch (input) {
	case ADC_MICIN:
		adcdata = 0x1;
		input_source = 0x180;  /* set GPIO7 to select Mic */
		break;
	case ADC_LINEIN:
		adcdata = 0x2;
		break;
	case ADC_VIDEO:
		adcdata = 0x4;
		break;
	case ADC_AUX:
		adcdata = 0x8;
		break;
	case ADC_NONE:
		adcdata = 0x0;
		input_source = 0x0;  /* set to Digital */
		break;
	default:
		adcdata = 0x0;
		break;
	}

	if (i2c_unlock(hw))
		return -1;

	do {
		ret = hw_read_pci(hw, 0xEC);
	} while (!(ret & 0x800000)); /* i2c ready poll */
	hw_write_pci(hw, 0xEC, 0x05);  /* write to i2c status control */

	i2c_write(hw, 0x001a0080, 0x0e, 0x08);
	i2c_write(hw, 0x001a0080, 0x18, 0x0a);
	i2c_write(hw, 0x001a0080, 0x28, 0x86);
	i2c_write(hw, 0x001a0080, 0x2a, adcdata);

	if (mic20db) {
		i2c_write(hw, 0x001a0080, 0x1c, 0xf7);
		i2c_write(hw, 0x001a0080, 0x1e, 0xf7);
	} else {
		i2c_write(hw, 0x001a0080, 0x1c, 0xcf);
		i2c_write(hw, 0x001a0080, 0x1e, 0xcf);
	}

	if (!(hw_read_20kx(hw, ID0) & 0x100))
		i2c_write(hw, 0x001a0080, 0x16, 0x26);

	i2c_lock(hw);

	gpioorg = (u16)hw_read_20kx(hw,  GPIO);
	gpioorg &= 0xfe7f;
	gpioorg |= input_source;
	hw_write_20kx(hw, GPIO, gpioorg);

	return 0;
}