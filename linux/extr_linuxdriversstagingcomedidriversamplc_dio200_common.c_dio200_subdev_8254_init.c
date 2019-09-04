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
struct dio200_board {scalar_t__ has_clk_gat_sce; scalar_t__ is_pcie; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; scalar_t__ mmio; struct dio200_board* board_ptr; } ;
struct comedi_8254 {int /*<<< orphan*/  insn_config; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I8254_IO8 ; 
 struct comedi_8254* comedi_8254_init (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct comedi_8254* comedi_8254_mm_init (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  comedi_8254_subdevice_init (struct comedi_subdevice*,struct comedi_8254*) ; 
 int /*<<< orphan*/  comedi_set_spriv_auto_free (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dio200_subdev_8254_config ; 
 int /*<<< orphan*/  dio200_subdev_8254_set_clock_src (struct comedi_device*,struct comedi_subdevice*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dio200_subdev_8254_set_gate_src (struct comedi_device*,struct comedi_subdevice*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dio200_subdev_8254_init(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   unsigned int offset)
{
	const struct dio200_board *board = dev->board_ptr;
	struct comedi_8254 *i8254;
	unsigned int regshift;
	int chan;

	/*
	 * PCIe boards need the offset shifted in order to get the
	 * correct base address of the timer.
	 */
	if (board->is_pcie) {
		offset <<= 3;
		regshift = 3;
	} else {
		regshift = 0;
	}

	if (dev->mmio) {
		i8254 = comedi_8254_mm_init(dev->mmio + offset,
					    0, I8254_IO8, regshift);
	} else {
		i8254 = comedi_8254_init(dev->iobase + offset,
					 0, I8254_IO8, regshift);
	}
	if (!i8254)
		return -ENOMEM;

	comedi_8254_subdevice_init(s, i8254);

	i8254->insn_config = dio200_subdev_8254_config;

	/*
	 * There could be multiple timers so this driver does not
	 * use dev->pacer to save the i8254 pointer. Instead,
	 * comedi_8254_subdevice_init() saved the i8254 pointer in
	 * s->private.  Mark the subdevice as having private data
	 * to be automatically freed when the device is detached.
	 */
	comedi_set_spriv_auto_free(s);

	/* Initialize channels. */
	if (board->has_clk_gat_sce) {
		for (chan = 0; chan < 3; chan++) {
			/* Gate source 0 is VCC (logic 1). */
			dio200_subdev_8254_set_gate_src(dev, s, chan, 0);
			/* Clock source 0 is the dedicated clock input. */
			dio200_subdev_8254_set_clock_src(dev, s, chan, 0);
		}
	}

	return 0;
}