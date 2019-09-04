#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfcmrvl_private {int support_fw_dnld; int /*<<< orphan*/  ndev; } ;
struct nfcmrvl_platform_data {int /*<<< orphan*/  break_control; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  reset_n_io; int /*<<< orphan*/  hci_muxed; } ;
struct nci_uart {int /*<<< orphan*/  ndev; struct nfcmrvl_private* drv_data; TYPE_1__* tty; } ;
struct device {TYPE_2__* parent; } ;
struct TYPE_4__ {scalar_t__ of_node; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfcmrvl_private*) ; 
 int /*<<< orphan*/  NFCMRVL_PHY_UART ; 
 int PTR_ERR (struct nfcmrvl_private*) ; 
 int /*<<< orphan*/  break_control ; 
 int /*<<< orphan*/  flow_control ; 
 int /*<<< orphan*/  hci_muxed ; 
 struct nfcmrvl_private* nfcmrvl_nci_register_dev (int /*<<< orphan*/ ,struct nci_uart*,int /*<<< orphan*/ *,struct device*,struct nfcmrvl_platform_data*) ; 
 scalar_t__ nfcmrvl_uart_parse_dt (scalar_t__,struct nfcmrvl_platform_data*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  reset_n_io ; 
 int /*<<< orphan*/  uart_ops ; 

__attribute__((used)) static int nfcmrvl_nci_uart_open(struct nci_uart *nu)
{
	struct nfcmrvl_private *priv;
	struct nfcmrvl_platform_data *pdata = NULL;
	struct nfcmrvl_platform_data config;
	struct device *dev = nu->tty->dev;

	/*
	 * Platform data cannot be used here since usually it is already used
	 * by low level serial driver. We can try to retrieve serial device
	 * and check if DT entries were added.
	 */

	if (dev && dev->parent && dev->parent->of_node)
		if (nfcmrvl_uart_parse_dt(dev->parent->of_node, &config) == 0)
			pdata = &config;

	if (!pdata) {
		pr_info("No platform data / DT -> fallback to module params\n");
		config.hci_muxed = hci_muxed;
		config.reset_n_io = reset_n_io;
		config.flow_control = flow_control;
		config.break_control = break_control;
		pdata = &config;
	}

	priv = nfcmrvl_nci_register_dev(NFCMRVL_PHY_UART, nu, &uart_ops,
					dev, pdata);
	if (IS_ERR(priv))
		return PTR_ERR(priv);

	priv->support_fw_dnld = true;

	nu->drv_data = priv;
	nu->ndev = priv->ndev;

	return 0;
}