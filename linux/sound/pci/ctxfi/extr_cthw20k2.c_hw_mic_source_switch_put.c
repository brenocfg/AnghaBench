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
struct hw20k2 {int mic_source; } ;
struct hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_wm8775_input_select (struct hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_mic_source_switch_put(struct hw *hw, int position)
{
	struct hw20k2 *hw20k2 = (struct hw20k2 *)hw;

	if (position == hw20k2->mic_source)
		return 0;

	switch (position) {
	case 0:
		hw_wm8775_input_select(hw, 0, 0); /* Mic, 0dB */
		break;
	case 1:
		hw_wm8775_input_select(hw, 1, 0); /* FP Mic, 0dB */
		break;
	case 2:
		hw_wm8775_input_select(hw, 3, 0); /* Aux Ext, 0dB */
		break;
	default:
		return 0;
	}

	hw20k2->mic_source = position;

	return 1;
}