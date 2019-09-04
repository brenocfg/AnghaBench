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
struct tb_nhi {int dummy; } ;
struct tb {struct tb_nhi* nhi; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nhi_shutdown (struct tb_nhi*) ; 
 struct tb* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_domain_remove (struct tb*) ; 

__attribute__((used)) static void nhi_remove(struct pci_dev *pdev)
{
	struct tb *tb = pci_get_drvdata(pdev);
	struct tb_nhi *nhi = tb->nhi;

	pm_runtime_get_sync(&pdev->dev);
	pm_runtime_dont_use_autosuspend(&pdev->dev);
	pm_runtime_forbid(&pdev->dev);

	tb_domain_remove(tb);
	nhi_shutdown(nhi);
}