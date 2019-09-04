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
struct pcl818_board {scalar_t__ is_818; int /*<<< orphan*/ * ai_range_type; } ;
struct comedi_subdevice {int /*<<< orphan*/ * range_table; } ;
struct comedi_device {struct pcl818_board* board_ptr; } ;
struct comedi_devconfig {int* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  range718_bipolar0_5 ; 
 int /*<<< orphan*/  range718_bipolar1 ; 
 int /*<<< orphan*/  range718_unipolar1 ; 
 int /*<<< orphan*/  range718_unipolar2 ; 
 int /*<<< orphan*/  range_bipolar10 ; 
 int /*<<< orphan*/  range_bipolar2_5 ; 
 int /*<<< orphan*/  range_bipolar5 ; 
 int /*<<< orphan*/  range_pcl818l_h_ai ; 
 int /*<<< orphan*/  range_unipolar10 ; 
 int /*<<< orphan*/  range_unipolar5 ; 
 int /*<<< orphan*/  range_unknown ; 

__attribute__((used)) static void pcl818_set_ai_range_table(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct comedi_devconfig *it)
{
	const struct pcl818_board *board = dev->board_ptr;

	/* default to the range table from the boardinfo */
	s->range_table = board->ai_range_type;

	/* now check the user config option based on the boardtype */
	if (board->is_818) {
		if (it->options[4] == 1 || it->options[4] == 10) {
			/* secondary range list jumper selectable */
			s->range_table = &range_pcl818l_h_ai;
		}
	} else {
		switch (it->options[4]) {
		case 0:
			s->range_table = &range_bipolar10;
			break;
		case 1:
			s->range_table = &range_bipolar5;
			break;
		case 2:
			s->range_table = &range_bipolar2_5;
			break;
		case 3:
			s->range_table = &range718_bipolar1;
			break;
		case 4:
			s->range_table = &range718_bipolar0_5;
			break;
		case 6:
			s->range_table = &range_unipolar10;
			break;
		case 7:
			s->range_table = &range_unipolar5;
			break;
		case 8:
			s->range_table = &range718_unipolar2;
			break;
		case 9:
			s->range_table = &range718_unipolar1;
			break;
		default:
			s->range_table = &range_unknown;
			break;
		}
	}
}