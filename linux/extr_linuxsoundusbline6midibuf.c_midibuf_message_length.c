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

/* Variables and functions */

__attribute__((used)) static int midibuf_message_length(unsigned char code)
{
	int message_length;

	if (code < 0x80)
		message_length = -1;
	else if (code < 0xf0) {
		static const int length[] = { 3, 3, 3, 3, 2, 2, 3 };

		message_length = length[(code >> 4) - 8];
	} else {
		/*
		   Note that according to the MIDI specification 0xf2 is
		   the "Song Position Pointer", but this is used by Line 6
		   to send sysex messages to the host.
		 */
		static const int length[] = { -1, 2, -1, 2, -1, -1, 1, 1, 1, 1,
			1, 1, 1, -1, 1, 1
		};
		message_length = length[code & 0x0f];
	}

	return message_length;
}