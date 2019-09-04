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
struct calling_interface_buffer {int* output; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CLASS_INFO ; 
 int /*<<< orphan*/  SELECT_RFKILL ; 
 int /*<<< orphan*/  dell_fill_request (struct calling_interface_buffer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dell_send_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dell_rfkill_set(void *data, bool blocked)
{
	int disable = blocked ? 1 : 0;
	unsigned long radio = (unsigned long)data;
	int hwswitch_bit = (unsigned long)data - 1;
	struct calling_interface_buffer buffer;
	int hwswitch;
	int status;
	int ret;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	if (ret)
		return ret;
	status = buffer.output[1];

	dell_fill_request(&buffer, 0x2, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	if (ret)
		return ret;
	hwswitch = buffer.output[1];

	/* If the hardware switch controls this radio, and the hardware
	   switch is disabled, always disable the radio */
	if (ret == 0 && (hwswitch & BIT(hwswitch_bit)) &&
	    (status & BIT(0)) && !(status & BIT(16)))
		disable = 1;

	dell_fill_request(&buffer, 1 | (radio<<8) | (disable << 16), 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	return ret;
}