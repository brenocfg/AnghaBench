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
struct das16_private_struct {scalar_t__ extra_iobase; } ;
struct das16_board {int size; } ;
struct comedi_device {scalar_t__ iobase; struct das16_private_struct* private; struct das16_board* board_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_legacy_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  das16_free_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  das16_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void das16_detach(struct comedi_device *dev)
{
	const struct das16_board *board = dev->board_ptr;
	struct das16_private_struct *devpriv = dev->private;

	if (devpriv) {
		if (dev->iobase)
			das16_reset(dev);
		das16_free_dma(dev);

		if (devpriv->extra_iobase)
			release_region(devpriv->extra_iobase,
				       board->size & 0x3ff);
	}

	comedi_legacy_detach(dev);
}