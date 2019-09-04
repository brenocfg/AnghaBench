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
struct comedi_cmd {int dummy; } ;

/* Variables and functions */
#define  LAYOUT_4020 128 
 int /*<<< orphan*/  select_master_clock_4020 (struct comedi_device*,struct comedi_cmd const*) ; 

__attribute__((used)) static void select_master_clock(struct comedi_device *dev,
				const struct comedi_cmd *cmd)
{
	const struct pcidas64_board *board = dev->board_ptr;

	switch (board->layout) {
	case LAYOUT_4020:
		select_master_clock_4020(dev, cmd);
		break;
	default:
		break;
	}
}