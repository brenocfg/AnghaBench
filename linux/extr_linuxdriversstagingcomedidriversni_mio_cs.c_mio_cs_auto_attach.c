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
struct pcmcia_device {int config_flags; int /*<<< orphan*/  irq; struct comedi_device* priv; TYPE_1__** resource; } ;
struct ni_board_struct {int /*<<< orphan*/  name; } ;
struct comedi_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  iobase; int /*<<< orphan*/  board_name; struct ni_board_struct const* board_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int CONF_AUTO_SET_IO ; 
 int CONF_ENABLE_IRQ ; 
 int ENODEV ; 
 int comedi_pcmcia_enable (struct comedi_device*,int /*<<< orphan*/ ) ; 
 struct pcmcia_device* comedi_to_pcmcia_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  mio_pcmcia_config_loop ; 
 int ni_E_init (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ni_E_interrupt ; 
 int ni_alloc_private (struct comedi_device*) ; 
 struct ni_board_struct* ni_getboardtype (struct comedi_device*,struct pcmcia_device*) ; 
 int pcmcia_request_irq (struct pcmcia_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mio_cs_auto_attach(struct comedi_device *dev,
			      unsigned long context)
{
	struct pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	static const struct ni_board_struct *board;
	int ret;

	board = ni_getboardtype(dev, link);
	if (!board)
		return -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	link->config_flags |= CONF_AUTO_SET_IO | CONF_ENABLE_IRQ;
	ret = comedi_pcmcia_enable(dev, mio_pcmcia_config_loop);
	if (ret)
		return ret;
	dev->iobase = link->resource[0]->start;

	link->priv = dev;
	ret = pcmcia_request_irq(link, ni_E_interrupt);
	if (ret)
		return ret;
	dev->irq = link->irq;

	ret = ni_alloc_private(dev);
	if (ret)
		return ret;

	return ni_E_init(dev, 0, 1);
}