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
struct pn533_std_frame {scalar_t__ start_frame; scalar_t__ datalen; int datalen_checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  PN533_STD_FRAME_SOF ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 

bool pn533_rx_frame_is_ack(void *_frame)
{
	struct pn533_std_frame *frame = _frame;

	if (frame->start_frame != cpu_to_be16(PN533_STD_FRAME_SOF))
		return false;

	if (frame->datalen != 0 || frame->datalen_checksum != 0xFF)
		return false;

	return true;
}