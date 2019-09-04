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
struct das16_board {int id; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; scalar_t__ iobase; struct das16_board* board_ptr; } ;
struct comedi_devconfig {int dummy; } ;

/* Variables and functions */
 scalar_t__ DAS16_DIO_REG ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static int das16_probe(struct comedi_device *dev, struct comedi_devconfig *it)
{
	const struct das16_board *board = dev->board_ptr;
	int diobits;

	/* diobits indicates boards */
	diobits = inb(dev->iobase + DAS16_DIO_REG) & 0xf0;
	if (board->id != diobits) {
		dev_err(dev->class_dev,
			"requested board's id bits are incorrect (0x%x != 0x%x)\n",
			board->id, diobits);
		return -EINVAL;
	}

	return 0;
}