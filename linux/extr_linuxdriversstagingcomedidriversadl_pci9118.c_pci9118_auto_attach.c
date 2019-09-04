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
struct pci_dev {int dummy; } ;
struct pci9118_boardinfo {int /*<<< orphan*/  name; } ;
struct comedi_device {int /*<<< orphan*/  board_name; struct pci9118_boardinfo const* board_ptr; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (struct pci9118_boardinfo*) ; 
 int ENODEV ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 struct pci9118_boardinfo* pci9118_boards ; 
 int pci9118_common_attach (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 

__attribute__((used)) static int pci9118_auto_attach(struct comedi_device *dev,
			       unsigned long context)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const struct pci9118_boardinfo *board = NULL;

	if (context < ARRAY_SIZE(pci9118_boards))
		board = &pci9118_boards[context];
	if (!board)
		return -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	/*
	 * Need to 'get' the PCI device to match the 'put' in pci9118_detach().
	 * (The 'put' also matches the implicit 'get' by pci9118_find_pci().)
	 */
	pci_dev_get(pcidev);
	/* no external mux, no sample-hold delay */
	return pci9118_common_attach(dev, 0, 0);
}