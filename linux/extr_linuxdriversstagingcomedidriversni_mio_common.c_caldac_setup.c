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
struct ni_private {unsigned int* caldac_maxdata_list; } ;
struct ni_board_struct {int* caldac; } ;
struct comedi_subdevice {int n_chan; unsigned int* maxdata_list; int maxdata; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; struct ni_board_struct* board_ptr; } ;
struct TYPE_2__ {int n_bits; int n_chans; } ;

/* Variables and functions */
 int MAX_N_CALDACS ; 
 int caldac_none ; 
 TYPE_1__* caldacs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ni_write_caldac (struct comedi_device*,int,int) ; 

__attribute__((used)) static void caldac_setup(struct comedi_device *dev, struct comedi_subdevice *s)
{
	const struct ni_board_struct *board = dev->board_ptr;
	struct ni_private *devpriv = dev->private;
	int i, j;
	int n_dacs;
	int n_chans = 0;
	int n_bits;
	int diffbits = 0;
	int type;
	int chan;

	type = board->caldac[0];
	if (type == caldac_none)
		return;
	n_bits = caldacs[type].n_bits;
	for (i = 0; i < 3; i++) {
		type = board->caldac[i];
		if (type == caldac_none)
			break;
		if (caldacs[type].n_bits != n_bits)
			diffbits = 1;
		n_chans += caldacs[type].n_chans;
	}
	n_dacs = i;
	s->n_chan = n_chans;

	if (diffbits) {
		unsigned int *maxdata_list = devpriv->caldac_maxdata_list;

		if (n_chans > MAX_N_CALDACS)
			dev_err(dev->class_dev,
				"BUG! MAX_N_CALDACS too small\n");
		s->maxdata_list = maxdata_list;
		chan = 0;
		for (i = 0; i < n_dacs; i++) {
			type = board->caldac[i];
			for (j = 0; j < caldacs[type].n_chans; j++) {
				maxdata_list[chan] =
				    (1 << caldacs[type].n_bits) - 1;
				chan++;
			}
		}

		for (chan = 0; chan < s->n_chan; chan++)
			ni_write_caldac(dev, i, s->maxdata_list[i] / 2);
	} else {
		type = board->caldac[0];
		s->maxdata = (1 << caldacs[type].n_bits) - 1;

		for (chan = 0; chan < s->n_chan; chan++)
			ni_write_caldac(dev, i, s->maxdata / 2);
	}
}