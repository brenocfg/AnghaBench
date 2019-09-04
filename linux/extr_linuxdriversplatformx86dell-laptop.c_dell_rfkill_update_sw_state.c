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
struct rfkill {int dummy; } ;
struct calling_interface_buffer {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CLASS_INFO ; 
 int /*<<< orphan*/  SELECT_RFKILL ; 
 int /*<<< orphan*/  dell_fill_request (struct calling_interface_buffer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dell_send_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rfkill_blocked (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_set_sw_state (struct rfkill*,int) ; 

__attribute__((used)) static void dell_rfkill_update_sw_state(struct rfkill *rfkill, int radio,
					int status)
{
	if (status & BIT(0)) {
		/* Has hw-switch, sync sw_state to BIOS */
		struct calling_interface_buffer buffer;
		int block = rfkill_blocked(rfkill);
		dell_fill_request(&buffer,
				   1 | (radio << 8) | (block << 16), 0, 0, 0);
		dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	} else {
		/* No hw-switch, sync BIOS state to sw_state */
		rfkill_set_sw_state(rfkill, !!(status & BIT(radio + 16)));
	}
}