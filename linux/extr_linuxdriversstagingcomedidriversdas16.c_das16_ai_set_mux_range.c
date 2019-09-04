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
struct das16_board {size_t ai_pg; } ;
struct comedi_device {scalar_t__ iobase; struct das16_board* board_ptr; } ;

/* Variables and functions */
 scalar_t__ DAS16_GAIN_REG ; 
 scalar_t__ DAS16_MUX_REG ; 
 unsigned int** das16_gainlists ; 
 size_t das16_pg_none ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void das16_ai_set_mux_range(struct comedi_device *dev,
				   unsigned int first_chan,
				   unsigned int last_chan,
				   unsigned int range)
{
	const struct das16_board *board = dev->board_ptr;

	/* set multiplexer */
	outb(first_chan | (last_chan << 4), dev->iobase + DAS16_MUX_REG);

	/* some boards do not have programmable gain */
	if (board->ai_pg == das16_pg_none)
		return;

	/*
	 * Set gain (this is also burst rate register but according to
	 * computer boards manual, burst rate does nothing, even on
	 * keithley cards).
	 */
	outb((das16_gainlists[board->ai_pg])[range],
	     dev->iobase + DAS16_GAIN_REG);
}