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
struct comedi_subdevice {int n_chan; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pcmda12_ao_reset(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	int i;

	for (i = 0; i < s->n_chan; ++i) {
		outb(0, dev->iobase + (i * 2));
		outb(0, dev->iobase + (i * 2) + 1);
	}
	/* Initiate transfer by reading one of the AO registers. */
	inb(dev->iobase);
}