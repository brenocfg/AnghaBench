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
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipw_down (struct ipw_priv*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ipw_priv* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void ipw_pci_shutdown(struct pci_dev *pdev)
{
	struct ipw_priv *priv = pci_get_drvdata(pdev);

	/* Take down the device; powers it off, etc. */
	ipw_down(priv);

	pci_disable_device(pdev);
}