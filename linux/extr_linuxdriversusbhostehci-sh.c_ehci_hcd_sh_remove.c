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
struct usb_hcd {int dummy; } ;
struct platform_device {int dummy; } ;
struct ehci_sh_priv {int /*<<< orphan*/  iclk; int /*<<< orphan*/  fclk; struct usb_hcd* hcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct ehci_sh_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_hcd_sh_remove(struct platform_device *pdev)
{
	struct ehci_sh_priv *priv = platform_get_drvdata(pdev);
	struct usb_hcd *hcd = priv->hcd;

	usb_remove_hcd(hcd);
	usb_put_hcd(hcd);

	clk_disable(priv->fclk);
	clk_disable(priv->iclk);

	return 0;
}