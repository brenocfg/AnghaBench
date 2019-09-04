#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_2__* async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ stop_src; } ;
struct TYPE_4__ {int /*<<< orphan*/  inttrig; TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  NISTC_INTB_ENA_AO_BC_TC ; 
 int /*<<< orphan*/  NISTC_INTB_ENA_REG ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  ni_ao_inttrig ; 
 int /*<<< orphan*/  ni_set_bits (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ni_ao_cmd_set_interrupts(struct comedi_device *dev,
				     struct comedi_subdevice *s)
{
	if (s->async->cmd.stop_src == TRIG_COUNT)
		ni_set_bits(dev, NISTC_INTB_ENA_REG,
			    NISTC_INTB_ENA_AO_BC_TC, 1);

	s->async->inttrig = ni_ao_inttrig;
}