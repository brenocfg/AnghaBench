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
struct pcidas64_board {int layout; } ;
struct comedi_device {struct pcidas64_board* board_ptr; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LAYOUT_4020 128 
 int ai_config_master_clock_4020 (struct comedi_device*,unsigned int*) ; 

__attribute__((used)) static int ai_config_master_clock(struct comedi_device *dev, unsigned int *data)
{
	const struct pcidas64_board *board = dev->board_ptr;

	switch (board->layout) {
	case LAYOUT_4020:
		return ai_config_master_clock_4020(dev, data);
	default:
		return -EINVAL;
	}

	return -EINVAL;
}