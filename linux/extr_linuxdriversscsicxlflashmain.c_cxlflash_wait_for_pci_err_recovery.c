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
struct cxlflash_cfg {int /*<<< orphan*/  reset_waitq; struct pci_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXLFLASH_PCI_ERROR_RECOVERY_TIMEOUT ; 
 scalar_t__ pci_channel_offline (struct pci_dev*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxlflash_wait_for_pci_err_recovery(struct cxlflash_cfg *cfg)
{
	struct pci_dev *pdev = cfg->dev;

	if (pci_channel_offline(pdev))
		wait_event_timeout(cfg->reset_waitq,
				   !pci_channel_offline(pdev),
				   CXLFLASH_PCI_ERROR_RECOVERY_TIMEOUT);
}