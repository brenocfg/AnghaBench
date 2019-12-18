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
struct sata_oxnas_host_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst_phy; int /*<<< orphan*/  rst_link; int /*<<< orphan*/  rst_sata; int /*<<< orphan*/  core_base; int /*<<< orphan*/  sgdma_base; int /*<<< orphan*/  port_base; int /*<<< orphan*/  irq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ata_host {struct sata_oxnas_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_host_detach (struct ata_host*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 struct ata_host* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sata_oxnas_remove(struct platform_device *ofdev)
{
	struct ata_host *host = dev_get_drvdata(&ofdev->dev);
	struct sata_oxnas_host_priv *host_priv = host->private_data;

	ata_host_detach(host);

	irq_dispose_mapping(host_priv->irq);
	iounmap(host_priv->port_base);
	iounmap(host_priv->sgdma_base);
	iounmap(host_priv->core_base);

	/* reset Controller, Link and PHY */
	reset_control_assert(host_priv->rst_sata);
	reset_control_assert(host_priv->rst_link);
	reset_control_assert(host_priv->rst_phy);

	/* Disable the clock to the SATA block */
	clk_disable_unprepare(host_priv->clk);
	clk_put(host_priv->clk);

	return 0;
}