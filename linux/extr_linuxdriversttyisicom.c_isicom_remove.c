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
struct pci_dev {int dummy; } ;
struct isi_board {unsigned int port_count; int index; scalar_t__ base; int /*<<< orphan*/  irq; TYPE_1__* ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  card_count ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct isi_board*) ; 
 int /*<<< orphan*/  isicom_normal ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct isi_board* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isicom_remove(struct pci_dev *pdev)
{
	struct isi_board *board = pci_get_drvdata(pdev);
	unsigned int i;

	for (i = 0; i < board->port_count; i++) {
		tty_unregister_device(isicom_normal, board->index * 16 + i);
		tty_port_destroy(&board->ports[i].port);
	}

	free_irq(board->irq, board);
	pci_release_region(pdev, 3);
	board->base = 0;
	card_count--;
	pci_disable_device(pdev);
}