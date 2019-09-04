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
struct hw {int dummy; } ;
typedef  enum ADCSRC { ____Placeholder_ADCSRC } ADCSRC ;

/* Variables and functions */
#define  ADC_LINEIN 129 
#define  ADC_MICIN 128 
 int /*<<< orphan*/  GPIO_DATA ; 
 int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_wm8775_input_select (struct hw*,int,int) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hw_adc_input_select(struct hw *hw, enum ADCSRC type)
{
	u32 data;
	data = hw_read_20kx(hw, GPIO_DATA);
	switch (type) {
	case ADC_MICIN:
		data |= (0x1 << 14);
		hw_write_20kx(hw, GPIO_DATA, data);
		hw_wm8775_input_select(hw, 0, 20); /* Mic, 20dB */
		break;
	case ADC_LINEIN:
		data &= ~(0x1 << 14);
		hw_write_20kx(hw, GPIO_DATA, data);
		hw_wm8775_input_select(hw, 1, 0); /* Line-in, 0dB */
		break;
	default:
		break;
	}

	return 0;
}