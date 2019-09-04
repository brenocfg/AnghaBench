#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {unsigned int irq; int /*<<< orphan*/  dev; } ;
struct dgnc_board {int device; unsigned int irq; int membase; unsigned int iobase; int bd_uart_offset; int bd_dividend; int /*<<< orphan*/  state_wait; TYPE_3__* bd_ops; int /*<<< orphan*/  helper_tasklet; struct pci_dev* pdev; void* iobase_end; void* membase_end; int /*<<< orphan*/  state; int /*<<< orphan*/  bd_intr_lock; int /*<<< orphan*/  bd_lock; int /*<<< orphan*/  maxports; int /*<<< orphan*/  name; int /*<<< orphan*/  boardnum; } ;
struct TYPE_6__ {int /*<<< orphan*/  tasklet; } ;
struct TYPE_5__ {int /*<<< orphan*/  maxports; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOARD_FOUND ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 struct dgnc_board* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PCI_DEVICE_CLASSIC_4_422_DID 131 
#define  PCI_DEVICE_CLASSIC_4_DID 130 
#define  PCI_DEVICE_CLASSIC_8_422_DID 129 
#define  PCI_DEVICE_CLASSIC_8_DID 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__ dgnc_cls_ops ; 
 int dgnc_do_remap (struct dgnc_board*) ; 
 TYPE_2__* dgnc_ids ; 
 int /*<<< orphan*/  dgnc_num_boards ; 
 TYPE_1__* dgnc_pci_tbl ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dgnc_board*) ; 
 struct dgnc_board* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 void* pci_resource_end (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dgnc_board *dgnc_found_board(struct pci_dev *pdev, int id)
{
	struct dgnc_board *brd;
	unsigned int pci_irq;
	int rc = 0;

	brd = kzalloc(sizeof(*brd), GFP_KERNEL);
	if (!brd)
		return ERR_PTR(-ENOMEM);

	/* store the info for the board we've found */
	brd->boardnum = dgnc_num_boards;
	brd->device = dgnc_pci_tbl[id].device;
	brd->pdev = pdev;
	brd->name = dgnc_ids[id].name;
	brd->maxports = dgnc_ids[id].maxports;
	init_waitqueue_head(&brd->state_wait);

	spin_lock_init(&brd->bd_lock);
	spin_lock_init(&brd->bd_intr_lock);

	brd->state		= BOARD_FOUND;

	pci_irq = pdev->irq;
	brd->irq = pci_irq;

	switch (brd->device) {
	case PCI_DEVICE_CLASSIC_4_DID:
	case PCI_DEVICE_CLASSIC_8_DID:
	case PCI_DEVICE_CLASSIC_4_422_DID:
	case PCI_DEVICE_CLASSIC_8_422_DID:
		/*
		 * For PCI ClassicBoards
		 * PCI Local Address (i.e. "resource" number) space
		 * 0	PLX Memory Mapped Config
		 * 1	PLX I/O Mapped Config
		 * 2	I/O Mapped UARTs and Status
		 * 3	Memory Mapped VPD
		 * 4	Memory Mapped UARTs and Status
		 */

		brd->membase = pci_resource_start(pdev, 4);

		if (!brd->membase) {
			dev_err(&brd->pdev->dev,
				"Card has no PCI IO resources, failing.\n");
			rc = -ENODEV;
			goto failed;
		}

		brd->membase_end = pci_resource_end(pdev, 4);

		if (brd->membase & 1)
			brd->membase &= ~3;
		else
			brd->membase &= ~15;

		brd->iobase	= pci_resource_start(pdev, 1);
		brd->iobase_end = pci_resource_end(pdev, 1);
		brd->iobase	= ((unsigned int)(brd->iobase)) & 0xFFFE;

		brd->bd_ops = &dgnc_cls_ops;

		brd->bd_uart_offset = 0x8;
		brd->bd_dividend = 921600;

		rc = dgnc_do_remap(brd);
		if (rc < 0)
			goto failed;

		/*
		 * Enable Local Interrupt 1		  (0x1),
		 * Local Interrupt 1 Polarity Active high (0x2),
		 * Enable PCI interrupt			  (0x40)
		 */
		outb(0x43, brd->iobase + 0x4c);

		break;

	default:
		dev_err(&brd->pdev->dev,
			"Didn't find any compatible Neo/Classic PCI boards.\n");
		rc = -ENXIO;
		goto failed;
	}

	tasklet_init(&brd->helper_tasklet,
		     brd->bd_ops->tasklet,
		     (unsigned long)brd);

	wake_up_interruptible(&brd->state_wait);

	return brd;

failed:
	kfree(brd);

	return ERR_PTR(rc);
}