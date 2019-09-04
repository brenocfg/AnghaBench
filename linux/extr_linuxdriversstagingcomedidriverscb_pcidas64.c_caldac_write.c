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
#define  LAYOUT_4020 130 
#define  LAYOUT_60XX 129 
#define  LAYOUT_64XX 128 
 int /*<<< orphan*/  caldac_8800_write (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  caldac_i2c_write (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static void caldac_write(struct comedi_device *dev, unsigned int channel,
			 unsigned int value)
{
	const struct pcidas64_board *board = dev->board_ptr;

	switch (board->layout) {
	case LAYOUT_60XX:
	case LAYOUT_64XX:
		caldac_8800_write(dev, channel, value);
		break;
	case LAYOUT_4020:
		caldac_i2c_write(dev, channel, value);
		break;
	default:
		break;
	}
}