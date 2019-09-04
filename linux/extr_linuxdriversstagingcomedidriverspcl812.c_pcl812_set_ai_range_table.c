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
struct pcl812_private {int range_correction; } ;
struct pcl812_board {int board_type; int /*<<< orphan*/ * rangelist_ai; } ;
struct comedi_subdevice {int /*<<< orphan*/ * range_table; } ;
struct comedi_device {struct pcl812_private* private; struct pcl812_board* board_ptr; } ;
struct comedi_devconfig {int* options; } ;

/* Variables and functions */
#define  BOARD_ACL8113 132 
#define  BOARD_ISO813 131 
#define  BOARD_PCL812 130 
#define  BOARD_PCL812PG 129 
#define  BOARD_PCL813B 128 
 int /*<<< orphan*/  range812_bipolar0_3125 ; 
 int /*<<< orphan*/  range812_bipolar0_625 ; 
 int /*<<< orphan*/  range812_bipolar1_25 ; 
 int /*<<< orphan*/  range_acl8113_1_2_ai ; 
 int /*<<< orphan*/  range_acl8113_1_ai ; 
 int /*<<< orphan*/  range_acl8113_2_2_ai ; 
 int /*<<< orphan*/  range_acl8113_2_ai ; 
 int /*<<< orphan*/  range_bipolar10 ; 
 int /*<<< orphan*/  range_bipolar2_5 ; 
 int /*<<< orphan*/  range_bipolar5 ; 
 int /*<<< orphan*/  range_iso813_1_2_ai ; 
 int /*<<< orphan*/  range_iso813_1_ai ; 
 int /*<<< orphan*/  range_iso813_2_2_ai ; 
 int /*<<< orphan*/  range_iso813_2_ai ; 
 int /*<<< orphan*/  range_pcl812pg2_ai ; 
 int /*<<< orphan*/  range_pcl813b2_ai ; 

__attribute__((used)) static void pcl812_set_ai_range_table(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct comedi_devconfig *it)
{
	const struct pcl812_board *board = dev->board_ptr;
	struct pcl812_private *devpriv = dev->private;

	switch (board->board_type) {
	case BOARD_PCL812PG:
		if (it->options[4] == 1)
			s->range_table = &range_pcl812pg2_ai;
		else
			s->range_table = board->rangelist_ai;
		break;
	case BOARD_PCL812:
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
			s->range_table = &range812_bipolar1_25;
			break;
		case 4:
			s->range_table = &range812_bipolar0_625;
			break;
		case 5:
			s->range_table = &range812_bipolar0_3125;
			break;
		default:
			s->range_table = &range_bipolar10;
			break;
		}
		break;
	case BOARD_PCL813B:
		if (it->options[1] == 1)
			s->range_table = &range_pcl813b2_ai;
		else
			s->range_table = board->rangelist_ai;
		break;
	case BOARD_ISO813:
		switch (it->options[1]) {
		case 0:
			s->range_table = &range_iso813_1_ai;
			break;
		case 1:
			s->range_table = &range_iso813_1_2_ai;
			break;
		case 2:
			s->range_table = &range_iso813_2_ai;
			devpriv->range_correction = 1;
			break;
		case 3:
			s->range_table = &range_iso813_2_2_ai;
			devpriv->range_correction = 1;
			break;
		default:
			s->range_table = &range_iso813_1_ai;
			break;
		}
		break;
	case BOARD_ACL8113:
		switch (it->options[1]) {
		case 0:
			s->range_table = &range_acl8113_1_ai;
			break;
		case 1:
			s->range_table = &range_acl8113_1_2_ai;
			break;
		case 2:
			s->range_table = &range_acl8113_2_ai;
			devpriv->range_correction = 1;
			break;
		case 3:
			s->range_table = &range_acl8113_2_2_ai;
			devpriv->range_correction = 1;
			break;
		default:
			s->range_table = &range_acl8113_1_ai;
			break;
		}
		break;
	default:
		s->range_table = board->rangelist_ai;
		break;
	}
}