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
struct pcidas64_board {struct hw_fifo_info* ai_fifo; } ;
struct hw_fifo_info {unsigned int sample_packing_ratio; unsigned int num_segments; } ;
struct comedi_device {struct pcidas64_board* board_ptr; } ;

/* Variables and functions */
 int set_ai_fifo_segment_length (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static int set_ai_fifo_size(struct comedi_device *dev, unsigned int num_samples)
{
	const struct pcidas64_board *board = dev->board_ptr;
	unsigned int num_fifo_entries;
	int retval;
	const struct hw_fifo_info *const fifo = board->ai_fifo;

	num_fifo_entries = num_samples / fifo->sample_packing_ratio;

	retval = set_ai_fifo_segment_length(dev,
					    num_fifo_entries /
					    fifo->num_segments);
	if (retval < 0)
		return retval;

	return retval * fifo->num_segments * fifo->sample_packing_ratio;
}