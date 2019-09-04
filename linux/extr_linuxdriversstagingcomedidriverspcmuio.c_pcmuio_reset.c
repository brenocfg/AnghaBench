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
struct pcmuio_board {int num_asics; } ;
struct comedi_device {struct pcmuio_board* board_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCMUIO_PAGE_ENAB ; 
 int /*<<< orphan*/  PCMUIO_PAGE_INT_ID ; 
 int /*<<< orphan*/  PCMUIO_PAGE_POL ; 
 int /*<<< orphan*/  pcmuio_write (struct comedi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcmuio_reset(struct comedi_device *dev)
{
	const struct pcmuio_board *board = dev->board_ptr;
	int asic;

	for (asic = 0; asic < board->num_asics; ++asic) {
		/* first, clear all the DIO port bits */
		pcmuio_write(dev, 0, asic, 0, 0);
		pcmuio_write(dev, 0, asic, 0, 3);

		/* Next, clear all the paged registers for each page */
		pcmuio_write(dev, 0, asic, PCMUIO_PAGE_POL, 0);
		pcmuio_write(dev, 0, asic, PCMUIO_PAGE_ENAB, 0);
		pcmuio_write(dev, 0, asic, PCMUIO_PAGE_INT_ID, 0);
	}
}