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
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; struct comedi_8254* private; int /*<<< orphan*/  insn_config; int /*<<< orphan*/  insn_write; int /*<<< orphan*/  insn_read; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_8254 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_COUNTER ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 int /*<<< orphan*/  comedi_8254_insn_config ; 
 int /*<<< orphan*/  comedi_8254_insn_read ; 
 int /*<<< orphan*/  comedi_8254_insn_write ; 
 int /*<<< orphan*/  range_unknown ; 

void comedi_8254_subdevice_init(struct comedi_subdevice *s,
				struct comedi_8254 *i8254)
{
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 3;
	s->maxdata	= 0xffff;
	s->range_table	= &range_unknown;
	s->insn_read	= comedi_8254_insn_read;
	s->insn_write	= comedi_8254_insn_write;
	s->insn_config	= comedi_8254_insn_config;

	s->private	= i8254;
}