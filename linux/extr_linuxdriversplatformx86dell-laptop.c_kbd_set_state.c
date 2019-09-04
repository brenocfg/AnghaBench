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
struct kbd_state {int triggers; int timeout_value; int timeout_unit; int als_setting; int level; int timeout_value_ac; int timeout_unit_ac; int /*<<< orphan*/  mode_bit; } ;
struct calling_interface_buffer {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASS_KBD_BACKLIGHT ; 
 int /*<<< orphan*/  SELECT_KBD_BACKLIGHT ; 
 int /*<<< orphan*/  dell_fill_request (struct calling_interface_buffer*,int,int,int,int /*<<< orphan*/ ) ; 
 int dell_send_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kbd_set_state(struct kbd_state *state)
{
	struct calling_interface_buffer buffer;
	int ret;
	u32 input1;
	u32 input2;

	input1 = BIT(state->mode_bit) & 0xFFFF;
	input1 |= (state->triggers & 0xFF) << 16;
	input1 |= (state->timeout_value & 0x3F) << 24;
	input1 |= (state->timeout_unit & 0x3) << 30;
	input2 = state->als_setting & 0xFF;
	input2 |= (state->level & 0xFF) << 16;
	input2 |= (state->timeout_value_ac & 0x3F) << 24;
	input2 |= (state->timeout_unit_ac & 0x3) << 30;
	dell_fill_request(&buffer, 0x2, input1, input2, 0);
	ret = dell_send_request(&buffer,
				CLASS_KBD_BACKLIGHT, SELECT_KBD_BACKLIGHT);

	return ret;
}