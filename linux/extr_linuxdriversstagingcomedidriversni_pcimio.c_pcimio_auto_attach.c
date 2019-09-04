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
struct pci_dev {unsigned int irq; } ;
struct ni_private {int is_m_series; int is_6xxx; int is_611x; int is_6143; int is_622x; int is_625x; int is_628x; int is_67xx; int is_6711; int is_6713; void** gpct_mite_ring; int /*<<< orphan*/  mite; void* cdo_mite_ring; void* ao_mite_ring; void* ai_mite_ring; } ;
struct ni_board_struct {int reg_type; int /*<<< orphan*/  name; } ;
struct comedi_device {unsigned int irq; TYPE_1__* subdevices; int /*<<< orphan*/  board_name; struct ni_private* private; struct ni_board_struct const* board_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buf_change; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (struct ni_board_struct*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 size_t NI_AI_SUBDEV ; 
 size_t NI_AO_SUBDEV ; 
 size_t NI_DIO_SUBDEV ; 
 size_t NI_GPCT_SUBDEV (int) ; 
 int comedi_pci_enable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  init_6143 (struct comedi_device*) ; 
 int /*<<< orphan*/  m_series_init_eeprom_buffer (struct comedi_device*) ; 
 void* mite_alloc_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_attach (struct comedi_device*,int) ; 
 int ni_E_init (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ni_E_interrupt ; 
 int ni_alloc_private (struct comedi_device*) ; 
 struct ni_board_struct* ni_boards ; 
 int ni_reg_611x ; 
 int ni_reg_6143 ; 
 int ni_reg_622x ; 
 int ni_reg_625x ; 
 int ni_reg_628x ; 
 int ni_reg_6711 ; 
 int ni_reg_6713 ; 
 int ni_reg_67xx_mask ; 
 int ni_reg_6xxx_mask ; 
 int ni_reg_m_series_mask ; 
 int /*<<< orphan*/  pcimio_ai_change ; 
 int /*<<< orphan*/  pcimio_ao_change ; 
 int /*<<< orphan*/  pcimio_dio_change ; 
 int /*<<< orphan*/  pcimio_gpct0_change ; 
 int /*<<< orphan*/  pcimio_gpct1_change ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 

__attribute__((used)) static int pcimio_auto_attach(struct comedi_device *dev,
			      unsigned long context)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const struct ni_board_struct *board = NULL;
	struct ni_private *devpriv;
	unsigned int irq;
	int ret;

	if (context < ARRAY_SIZE(ni_boards))
		board = &ni_boards[context];
	if (!board)
		return -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	ret = comedi_pci_enable(dev);
	if (ret)
		return ret;

	ret = ni_alloc_private(dev);
	if (ret)
		return ret;
	devpriv = dev->private;

	devpriv->mite = mite_attach(dev, false);	/* use win0 */
	if (!devpriv->mite)
		return -ENOMEM;

	if (board->reg_type & ni_reg_m_series_mask)
		devpriv->is_m_series = 1;
	if (board->reg_type & ni_reg_6xxx_mask)
		devpriv->is_6xxx = 1;
	if (board->reg_type == ni_reg_611x)
		devpriv->is_611x = 1;
	if (board->reg_type == ni_reg_6143)
		devpriv->is_6143 = 1;
	if (board->reg_type == ni_reg_622x)
		devpriv->is_622x = 1;
	if (board->reg_type == ni_reg_625x)
		devpriv->is_625x = 1;
	if (board->reg_type == ni_reg_628x)
		devpriv->is_628x = 1;
	if (board->reg_type & ni_reg_67xx_mask)
		devpriv->is_67xx = 1;
	if (board->reg_type == ni_reg_6711)
		devpriv->is_6711 = 1;
	if (board->reg_type == ni_reg_6713)
		devpriv->is_6713 = 1;

	devpriv->ai_mite_ring = mite_alloc_ring(devpriv->mite);
	if (!devpriv->ai_mite_ring)
		return -ENOMEM;
	devpriv->ao_mite_ring = mite_alloc_ring(devpriv->mite);
	if (!devpriv->ao_mite_ring)
		return -ENOMEM;
	devpriv->cdo_mite_ring = mite_alloc_ring(devpriv->mite);
	if (!devpriv->cdo_mite_ring)
		return -ENOMEM;
	devpriv->gpct_mite_ring[0] = mite_alloc_ring(devpriv->mite);
	if (!devpriv->gpct_mite_ring[0])
		return -ENOMEM;
	devpriv->gpct_mite_ring[1] = mite_alloc_ring(devpriv->mite);
	if (!devpriv->gpct_mite_ring[1])
		return -ENOMEM;

	if (devpriv->is_m_series)
		m_series_init_eeprom_buffer(dev);
	if (devpriv->is_6143)
		init_6143(dev);

	irq = pcidev->irq;
	if (irq) {
		ret = request_irq(irq, ni_E_interrupt, IRQF_SHARED,
				  dev->board_name, dev);
		if (ret == 0)
			dev->irq = irq;
	}

	ret = ni_E_init(dev, 0, 1);
	if (ret < 0)
		return ret;

	dev->subdevices[NI_AI_SUBDEV].buf_change = &pcimio_ai_change;
	dev->subdevices[NI_AO_SUBDEV].buf_change = &pcimio_ao_change;
	dev->subdevices[NI_GPCT_SUBDEV(0)].buf_change = &pcimio_gpct0_change;
	dev->subdevices[NI_GPCT_SUBDEV(1)].buf_change = &pcimio_gpct1_change;
	dev->subdevices[NI_DIO_SUBDEV].buf_change = &pcimio_dio_change;

	return 0;
}