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
struct pcidas64_board {scalar_t__ layout; } ;
struct comedi_device {struct pcidas64_board* board_ptr; } ;

/* Variables and functions */
 unsigned short ADC_SE_DIFF_BIT ; 
 scalar_t__ LAYOUT_60XX ; 
 scalar_t__ LAYOUT_64XX ; 

__attribute__((used)) static inline unsigned short se_diff_bit_6xxx(struct comedi_device *dev,
					      int use_differential)
{
	const struct pcidas64_board *board = dev->board_ptr;

	if ((board->layout == LAYOUT_64XX && !use_differential) ||
	    (board->layout == LAYOUT_60XX && use_differential))
		return ADC_SE_DIFF_BIT;

	return 0;
}