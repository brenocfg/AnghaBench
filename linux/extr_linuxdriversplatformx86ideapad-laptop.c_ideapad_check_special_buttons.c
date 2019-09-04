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
struct ideapad_private {TYPE_1__* adev; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPCCMD_R_SPECIAL_BUTTONS ; 
 int /*<<< orphan*/  ideapad_input_report (struct ideapad_private*,int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 int /*<<< orphan*/  read_ec_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ test_bit (unsigned long,unsigned long*) ; 

__attribute__((used)) static void ideapad_check_special_buttons(struct ideapad_private *priv)
{
	unsigned long bit, value;

	read_ec_data(priv->adev->handle, VPCCMD_R_SPECIAL_BUTTONS, &value);

	for (bit = 0; bit < 16; bit++) {
		if (test_bit(bit, &value)) {
			switch (bit) {
			case 0:	/* Z580 */
			case 6:	/* Z570 */
				/* Thermal Management button */
				ideapad_input_report(priv, 65);
				break;
			case 1:
				/* OneKey Theater button */
				ideapad_input_report(priv, 64);
				break;
			default:
				pr_info("Unknown special button: %lu\n", bit);
				break;
			}
		}
	}
}