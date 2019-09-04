#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci224_board {int ao_bits; int* ao_hwrange; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct pci224_board* board_ptr; } ;
struct comedi_cmd {int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 size_t CR_RANGE (int /*<<< orphan*/ ) ; 
 int PCI224_DACCON_POLAR_MASK ; 
 int PCI224_DACCON_POLAR_UNI ; 

__attribute__((used)) static void
pci224_ao_munge(struct comedi_device *dev, struct comedi_subdevice *s,
		void *data, unsigned int num_bytes, unsigned int chan_index)
{
	const struct pci224_board *board = dev->board_ptr;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned short *array = data;
	unsigned int length = num_bytes / sizeof(*array);
	unsigned int offset;
	unsigned int shift;
	unsigned int i;

	/* The hardware expects 16-bit numbers. */
	shift = 16 - board->ao_bits;
	/* Channels will be all bipolar or all unipolar. */
	if ((board->ao_hwrange[CR_RANGE(cmd->chanlist[0])] &
	     PCI224_DACCON_POLAR_MASK) == PCI224_DACCON_POLAR_UNI) {
		/* Unipolar */
		offset = 0;
	} else {
		/* Bipolar */
		offset = 32768;
	}
	/* Munge the data. */
	for (i = 0; i < length; i++)
		array[i] = (array[i] << shift) - offset;
}