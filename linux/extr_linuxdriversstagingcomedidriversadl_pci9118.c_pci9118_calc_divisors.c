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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct comedi_8254* pacer; } ;
struct comedi_cmd {scalar_t__ convert_src; } ;
struct comedi_8254 {unsigned int osc_base; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ TRIG_NOW ; 

__attribute__((used)) static void pci9118_calc_divisors(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  unsigned int *tim1, unsigned int *tim2,
				  unsigned int flags, int chans,
				  unsigned int *div1, unsigned int *div2,
				  unsigned int chnsshfront)
{
	struct comedi_8254 *pacer = dev->pacer;
	struct comedi_cmd *cmd = &s->async->cmd;

	*div1 = *tim2 / pacer->osc_base;	/* convert timer (burst) */
	*div2 = *tim1 / pacer->osc_base;	/* scan timer */
	*div2 = *div2 / *div1;			/* major timer is c1*c2 */
	if (*div2 < chans)
		*div2 = chans;

	*tim2 = *div1 * pacer->osc_base;	/* real convert timer */

	if (cmd->convert_src == TRIG_NOW && !chnsshfront) {
		/* use BSSH signal */
		if (*div2 < (chans + 2))
			*div2 = chans + 2;
	}

	*tim1 = *div1 * *div2 * pacer->osc_base;
}