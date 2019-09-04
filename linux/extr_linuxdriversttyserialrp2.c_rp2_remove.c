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
struct rp2_card {int /*<<< orphan*/  fw_loaded; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct rp2_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rp2_remove_ports (struct rp2_card*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rp2_remove(struct pci_dev *pdev)
{
	struct rp2_card *card = pci_get_drvdata(pdev);

	wait_for_completion(&card->fw_loaded);
	rp2_remove_ports(card);
}