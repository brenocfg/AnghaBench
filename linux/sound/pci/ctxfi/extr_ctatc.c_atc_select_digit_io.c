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
struct hw {int /*<<< orphan*/  (* select_adc_source ) (struct hw*,int /*<<< orphan*/ ) ;scalar_t__ (* is_adc_source_selected ) (struct hw*,int /*<<< orphan*/ ) ;} ;
struct ct_atc {struct hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_NONE ; 
 scalar_t__ stub1 (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atc_select_digit_io(struct ct_atc *atc)
{
	struct hw *hw = atc->hw;

	if (hw->is_adc_source_selected(hw, ADC_NONE))
		return 0;

	hw->select_adc_source(hw, ADC_NONE);

	return 0;
}