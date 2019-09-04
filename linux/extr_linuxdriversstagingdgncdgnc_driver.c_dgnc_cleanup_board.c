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
struct dgnc_board {int device; size_t boardnum; struct dgnc_board** channels; struct dgnc_board* ch_wqueue; struct dgnc_board* ch_equeue; struct dgnc_board* ch_rqueue; int /*<<< orphan*/ * re_map_membase; int /*<<< orphan*/  helper_tasklet; scalar_t__ irq; int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 int MAXPORTS ; 
#define  PCI_DEVICE_CLASSIC_4_422_DID 131 
#define  PCI_DEVICE_CLASSIC_4_DID 130 
#define  PCI_DEVICE_CLASSIC_8_422_DID 129 
#define  PCI_DEVICE_CLASSIC_8_DID 128 
 int /*<<< orphan*/ ** dgnc_board ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct dgnc_board*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dgnc_board*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dgnc_cleanup_board(struct dgnc_board *brd)
{
	int i = 0;

	if (!brd)
		return;

	switch (brd->device) {
	case PCI_DEVICE_CLASSIC_4_DID:
	case PCI_DEVICE_CLASSIC_8_DID:
	case PCI_DEVICE_CLASSIC_4_422_DID:
	case PCI_DEVICE_CLASSIC_8_422_DID:

		/* Tell card not to interrupt anymore. */
		outb(0, brd->iobase + 0x4c);
		break;

	default:
		break;
	}

	if (brd->irq)
		free_irq(brd->irq, brd);

	tasklet_kill(&brd->helper_tasklet);

	if (brd->re_map_membase) {
		iounmap(brd->re_map_membase);
		brd->re_map_membase = NULL;
	}

	for (i = 0; i < MAXPORTS ; i++) {
		if (brd->channels[i]) {
			kfree(brd->channels[i]->ch_rqueue);
			kfree(brd->channels[i]->ch_equeue);
			kfree(brd->channels[i]->ch_wqueue);
			kfree(brd->channels[i]);
			brd->channels[i] = NULL;
		}
	}

	dgnc_board[brd->boardnum] = NULL;

	kfree(brd);
}