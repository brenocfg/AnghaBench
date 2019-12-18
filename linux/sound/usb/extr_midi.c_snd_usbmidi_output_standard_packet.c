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
typedef  int /*<<< orphan*/  uint8_t ;
struct urb {int transfer_buffer_length; scalar_t__ transfer_buffer; } ;

/* Variables and functions */

__attribute__((used)) static void snd_usbmidi_output_standard_packet(struct urb *urb, uint8_t p0,
					       uint8_t p1, uint8_t p2,
					       uint8_t p3)
{

	uint8_t *buf =
		(uint8_t *)urb->transfer_buffer + urb->transfer_buffer_length;
	buf[0] = p0;
	buf[1] = p1;
	buf[2] = p2;
	buf[3] = p3;
	urb->transfer_buffer_length += 4;
}