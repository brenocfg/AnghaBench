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
struct moxa8250_board {unsigned int num_ports; int /*<<< orphan*/ * line; } ;

/* Variables and functions */
 struct moxa8250_board* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  serial8250_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void moxa8250_remove(struct pci_dev *pdev)
{
	struct moxa8250_board *brd = pci_get_drvdata(pdev);
	unsigned int i;

	for (i = 0; i < brd->num_ports; i++)
		serial8250_unregister_port(brd->line[i]);
}