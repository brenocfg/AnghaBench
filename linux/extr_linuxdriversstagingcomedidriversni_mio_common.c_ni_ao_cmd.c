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
struct ni_private {int ao_needs_arming; int /*<<< orphan*/  ao_mite_ring; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ irq; int /*<<< orphan*/  class_dev; struct ni_private* private; } ;
struct comedi_cmd {int dummy; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ni_ao_cmd_personalize (struct comedi_device*,struct comedi_cmd const*) ; 
 int /*<<< orphan*/  ni_ao_cmd_set_channels (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_ao_cmd_set_counters (struct comedi_device*,struct comedi_cmd const*) ; 
 int /*<<< orphan*/  ni_ao_cmd_set_fifo_mode (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_ao_cmd_set_interrupts (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_ao_cmd_set_stop_conditions (struct comedi_device*,struct comedi_cmd const*) ; 
 int /*<<< orphan*/  ni_ao_cmd_set_trigger (struct comedi_device*,struct comedi_cmd const*) ; 
 int /*<<< orphan*/  ni_ao_cmd_set_update (struct comedi_device*,struct comedi_cmd const*) ; 
 int /*<<< orphan*/  ni_cmd_set_mite_transfer (int /*<<< orphan*/ ,struct comedi_subdevice*,struct comedi_cmd const*,int) ; 

__attribute__((used)) static int ni_ao_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct ni_private *devpriv = dev->private;
	const struct comedi_cmd *cmd = &s->async->cmd;

	if (dev->irq == 0) {
		dev_err(dev->class_dev, "cannot run command without an irq");
		return -EIO;
	}

	/* ni_ao_reset should have already been done */
	ni_ao_cmd_personalize(dev, cmd);
	/* clearing fifo and preload happens elsewhere */

	ni_ao_cmd_set_trigger(dev, cmd);
	ni_ao_cmd_set_counters(dev, cmd);
	ni_ao_cmd_set_update(dev, cmd);
	ni_ao_cmd_set_channels(dev, s);
	ni_ao_cmd_set_stop_conditions(dev, cmd);
	ni_ao_cmd_set_fifo_mode(dev);
	ni_cmd_set_mite_transfer(devpriv->ao_mite_ring, s, cmd, 0x00ffffff);
	ni_ao_cmd_set_interrupts(dev, s);

	/*
	 * arm(ing) must happen later so that DMA can be setup and DACs
	 * preloaded with the actual output buffer before starting.
	 *
	 * start(ing) must happen _after_ arming is completed.  Starting can be
	 * done either via ni_ao_inttrig, or via an external trigger.
	 *
	 * **Currently, ni_ao_inttrig will automatically attempt a call to
	 * ni_ao_arm if the device still needs arming at that point.  This
	 * allows backwards compatibility.
	 */
	devpriv->ao_needs_arming = 1;
	return 0;
}