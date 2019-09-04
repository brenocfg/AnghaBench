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
struct qtnf_pcie_bus_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qtnf_en_txdone_irq (struct qtnf_pcie_bus_priv*) ; 
 int /*<<< orphan*/  qtnf_pcie_data_tx_reclaim (struct qtnf_pcie_bus_priv*) ; 

__attribute__((used)) static void qtnf_reclaim_tasklet_fn(unsigned long data)
{
	struct qtnf_pcie_bus_priv *priv = (void *)data;

	qtnf_pcie_data_tx_reclaim(priv);
	qtnf_en_txdone_irq(priv);
}