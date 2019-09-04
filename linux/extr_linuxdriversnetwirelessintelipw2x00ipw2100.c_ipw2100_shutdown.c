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
struct ipw2100_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipw2100_down (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ipw2100_priv* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void ipw2100_shutdown(struct pci_dev *pci_dev)
{
	struct ipw2100_priv *priv = pci_get_drvdata(pci_dev);

	/* Take down the device; powers it off, etc. */
	ipw2100_down(priv);

	pci_disable_device(pci_dev);
}