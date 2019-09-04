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
struct pcl812_private {int mode_reg_int; int /*<<< orphan*/  last_ai_chanspec; } ;
struct pcl812_board {unsigned int n_aochan; scalar_t__ has_dio; } ;
struct comedi_device {scalar_t__ iobase; struct pcl812_private* private; struct pcl812_board* board_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_PACK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCL812_AO_LSB_REG (unsigned int) ; 
 scalar_t__ PCL812_AO_MSB_REG (unsigned int) ; 
 int PCL812_CTRL_DISABLE_TRIG ; 
 scalar_t__ PCL812_CTRL_REG ; 
 scalar_t__ PCL812_DO_LSB_REG ; 
 scalar_t__ PCL812_DO_MSB_REG ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  pcl812_ai_clear_eoc (struct comedi_device*) ; 
 int /*<<< orphan*/  pcl812_ai_set_chan_range (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcl812_reset(struct comedi_device *dev)
{
	const struct pcl812_board *board = dev->board_ptr;
	struct pcl812_private *devpriv = dev->private;
	unsigned int chan;

	/* disable analog input trigger */
	outb(devpriv->mode_reg_int | PCL812_CTRL_DISABLE_TRIG,
	     dev->iobase + PCL812_CTRL_REG);
	pcl812_ai_clear_eoc(dev);

	/*
	 * Invalidate last_ai_chanspec then set analog input to
	 * known channel/range.
	 */
	devpriv->last_ai_chanspec = CR_PACK(16, 0, 0);
	pcl812_ai_set_chan_range(dev, CR_PACK(0, 0, 0), 0);

	/* set analog output channels to 0V */
	for (chan = 0; chan < board->n_aochan; chan++) {
		outb(0, dev->iobase + PCL812_AO_LSB_REG(chan));
		outb(0, dev->iobase + PCL812_AO_MSB_REG(chan));
	}

	/* set all digital outputs low */
	if (board->has_dio) {
		outb(0, dev->iobase + PCL812_DO_MSB_REG);
		outb(0, dev->iobase + PCL812_DO_LSB_REG);
	}
}