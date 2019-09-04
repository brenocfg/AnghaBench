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
struct hw {int model; } ;
typedef  enum ADCSRC { ____Placeholder_ADCSRC } ADCSRC ;

/* Variables and functions */
 int ADC_MICIN ; 
#define  CTSB055X 130 
#define  CTSB073X 129 
#define  CTUAA 128 
 int adc_input_select_SB055x (struct hw*,int,int) ; 
 int adc_input_select_SBx (struct hw*,int,int) ; 
 int adc_input_select_hendrix (struct hw*,int,int) ; 

__attribute__((used)) static int hw_adc_input_select(struct hw *hw, enum ADCSRC type)
{
	int state = type == ADC_MICIN;

	switch (hw->model) {
	case CTSB055X:
		return adc_input_select_SB055x(hw, type, state);
	case CTSB073X:
		return adc_input_select_hendrix(hw, type, state);
	case CTUAA:
		return adc_input_select_hendrix(hw, type, state);
	default:
		return adc_input_select_SBx(hw, type, state);
	}
}