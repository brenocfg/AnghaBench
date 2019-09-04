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
struct tsi721_device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct tsi721_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  tsi721_disable_ints (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_dma_stop_all (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void tsi721_shutdown(struct pci_dev *pdev)
{
	struct tsi721_device *priv = pci_get_drvdata(pdev);

	tsi_debug(EXIT, &pdev->dev, "enter");

	tsi721_disable_ints(priv);
	tsi721_dma_stop_all(priv);
	pci_clear_master(pdev);
	pci_disable_device(pdev);
}