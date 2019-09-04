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
struct pnp_dev {int /*<<< orphan*/  dev; } ;
struct ni_board_struct {int /*<<< orphan*/  name; } ;
struct comedi_device {unsigned int irq; int /*<<< orphan*/  board_name; struct ni_board_struct const* board_ptr; } ;
struct comedi_devconfig {unsigned long* options; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int comedi_request_region (struct comedi_device*,unsigned long,int) ; 
 int /*<<< orphan*/  comedi_set_hw_dev (struct comedi_device*,int /*<<< orphan*/ *) ; 
 int ni_E_init (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_E_interrupt ; 
 int ni_alloc_private (struct comedi_device*) ; 
 struct ni_board_struct* ni_atmio_probe (struct comedi_device*) ; 
 int* ni_irqpin ; 
 int ni_isapnp_find_board (struct pnp_dev**) ; 
 unsigned int pnp_irq (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pnp_port_start (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 

__attribute__((used)) static int ni_atmio_attach(struct comedi_device *dev,
			   struct comedi_devconfig *it)
{
	const struct ni_board_struct *board;
	struct pnp_dev *isapnp_dev;
	int ret;
	unsigned long iobase;
	unsigned int irq;

	ret = ni_alloc_private(dev);
	if (ret)
		return ret;

	iobase = it->options[0];
	irq = it->options[1];
	isapnp_dev = NULL;
	if (iobase == 0) {
		ret = ni_isapnp_find_board(&isapnp_dev);
		if (ret < 0)
			return ret;

		iobase = pnp_port_start(isapnp_dev, 0);
		irq = pnp_irq(isapnp_dev, 0);
		comedi_set_hw_dev(dev, &isapnp_dev->dev);
	}

	ret = comedi_request_region(dev, iobase, 0x20);
	if (ret)
		return ret;

	board = ni_atmio_probe(dev);
	if (!board)
		return -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	/* irq stuff */

	if (irq != 0) {
		if (irq > 15 || ni_irqpin[irq] == -1)
			return -EINVAL;
		ret = request_irq(irq, ni_E_interrupt, 0,
				  dev->board_name, dev);
		if (ret < 0)
			return -EINVAL;
		dev->irq = irq;
	}

	/* generic E series stuff in ni_mio_common.c */

	ret = ni_E_init(dev, ni_irqpin[dev->irq], 0);
	if (ret < 0)
		return ret;

	return 0;
}