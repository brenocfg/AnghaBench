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
struct jsm_board {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jsm_uart_port_init (struct jsm_board*) ; 
 struct jsm_board* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 

__attribute__((used)) static void jsm_io_resume(struct pci_dev *pdev)
{
	struct jsm_board *brd = pci_get_drvdata(pdev);

	pci_restore_state(pdev);
	pci_save_state(pdev);

	jsm_uart_port_init(brd);
}