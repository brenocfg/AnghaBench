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
#define  CTSB055X 130 
#define  CTSB073X 129 
#define  CTUAA 128 
 int is_adc_input_selected_SB055x (struct hw*,int) ; 
 int is_adc_input_selected_SBx (struct hw*,int) ; 
 int is_adc_input_selected_hendrix (struct hw*,int) ; 

__attribute__((used)) static int hw_is_adc_input_selected(struct hw *hw, enum ADCSRC type)
{
	switch (hw->model) {
	case CTSB055X:
		return is_adc_input_selected_SB055x(hw, type);
	case CTSB073X:
		return is_adc_input_selected_hendrix(hw, type);
	case CTUAA:
		return is_adc_input_selected_hendrix(hw, type);
	default:
		return is_adc_input_selected_SBx(hw, type);
	}
}