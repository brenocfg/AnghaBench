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
struct sata_oxnas_host_priv {int n_ports; int /*<<< orphan*/  rst_link; int /*<<< orphan*/  rst_sata; int /*<<< orphan*/  rst_phy; int /*<<< orphan*/  clk; } ;
struct ata_host {int /*<<< orphan*/ * ports; struct sata_oxnas_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sata_oxnas_link_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  workaround5458 (struct ata_host*) ; 

__attribute__((used)) static void sata_oxnas_reset_core(struct ata_host *ah)
{
	struct sata_oxnas_host_priv *host_priv = ah->private_data;
	int n;

	DPRINTK("ENTER\n");
	clk_prepare_enable(host_priv->clk);

	reset_control_assert(host_priv->rst_sata);
	reset_control_assert(host_priv->rst_link);
	reset_control_assert(host_priv->rst_phy);

	udelay(50);

	/* un-reset the PHY, then Link and Controller */
	reset_control_deassert(host_priv->rst_phy);
	udelay(50);

	reset_control_deassert(host_priv->rst_sata);
	reset_control_deassert(host_priv->rst_link);
	udelay(50);

	workaround5458(ah);
	/* tune for sata compatibility */
	sata_oxnas_link_write(ah->ports[0], 0x60, 0x2988);

	for (n = 0; n < host_priv->n_ports; n++) {
		/* each port in turn */
		sata_oxnas_link_write(ah->ports[n], 0x70, 0x55629);
	}
	udelay(50);
}