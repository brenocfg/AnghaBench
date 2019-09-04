#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int len; int /*<<< orphan*/ * rx_buf; } ;
struct spi_slave_system_control_priv {TYPE_1__ xfer; int /*<<< orphan*/  cmd; int /*<<< orphan*/  finished; struct spi_device* spi; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct spi_slave_system_control_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct spi_slave_system_control_priv*) ; 
 int spi_slave_system_control_submit (struct spi_slave_system_control_priv*) ; 

__attribute__((used)) static int spi_slave_system_control_probe(struct spi_device *spi)
{
	struct spi_slave_system_control_priv *priv;
	int ret;

	priv = devm_kzalloc(&spi->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->spi = spi;
	init_completion(&priv->finished);
	priv->xfer.rx_buf = &priv->cmd;
	priv->xfer.len = sizeof(priv->cmd);

	ret = spi_slave_system_control_submit(priv);
	if (ret)
		return ret;

	spi_set_drvdata(spi, priv);
	return 0;
}