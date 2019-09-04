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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier8250_priv {int /*<<< orphan*/  clk; } ;
struct uart_port {int line; int /*<<< orphan*/  fifosize; int /*<<< orphan*/  uartclk; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIPHIER_UART_DEFAULT_FIFO_SIZE ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uniphier_of_serial_setup(struct device *dev, struct uart_port *port,
				    struct uniphier8250_priv *priv)
{
	int ret;
	u32 prop;
	struct device_node *np = dev->of_node;

	ret = of_alias_get_id(np, "serial");
	if (ret < 0) {
		dev_err(dev, "failed to get alias id\n");
		return ret;
	}
	port->line = ret;

	/* Get clk rate through clk driver */
	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(dev, "failed to get clock\n");
		return PTR_ERR(priv->clk);
	}

	ret = clk_prepare_enable(priv->clk);
	if (ret < 0)
		return ret;

	port->uartclk = clk_get_rate(priv->clk);

	/* Check for fifo size */
	if (of_property_read_u32(np, "fifo-size", &prop) == 0)
		port->fifosize = prop;
	else
		port->fifosize = UNIPHIER_UART_DEFAULT_FIFO_SIZE;

	return 0;
}