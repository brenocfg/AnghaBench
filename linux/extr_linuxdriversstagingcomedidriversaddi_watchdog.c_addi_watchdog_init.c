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
struct comedi_subdevice {int n_chan; int maxdata; int /*<<< orphan*/  insn_write; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  insn_config; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  type; } ;
struct addi_watchdog_private {unsigned long iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_TIMER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 int /*<<< orphan*/  addi_watchdog_insn_config ; 
 int /*<<< orphan*/  addi_watchdog_insn_read ; 
 int /*<<< orphan*/  addi_watchdog_insn_write ; 
 struct addi_watchdog_private* comedi_alloc_spriv (struct comedi_subdevice*,int) ; 

int addi_watchdog_init(struct comedi_subdevice *s, unsigned long iobase)
{
	struct addi_watchdog_private *spriv;

	spriv = comedi_alloc_spriv(s, sizeof(*spriv));
	if (!spriv)
		return -ENOMEM;

	spriv->iobase = iobase;

	s->type		= COMEDI_SUBD_TIMER;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 1;
	s->maxdata	= 0xff;
	s->insn_config	= addi_watchdog_insn_config;
	s->insn_read	= addi_watchdog_insn_read;
	s->insn_write	= addi_watchdog_insn_write;

	return 0;
}