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
struct st_hba {int /*<<< orphan*/  mu_status; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MU_STATE_STARTING ; 
 struct st_hba* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  stex_handshake (struct st_hba*) ; 

__attribute__((used)) static int stex_resume(struct pci_dev *pdev)
{
	struct st_hba *hba = pci_get_drvdata(pdev);

	hba->mu_status = MU_STATE_STARTING;
	stex_handshake(hba);
	return 0;
}