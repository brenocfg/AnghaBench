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
struct pcidas64_board {int* ai_range_code; } ;
struct comedi_device {struct pcidas64_board* board_ptr; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int ai_range_bits_6xxx(const struct comedi_device *dev,
				       unsigned int range_index)
{
	const struct pcidas64_board *board = dev->board_ptr;

	return board->ai_range_code[range_index] << 8;
}