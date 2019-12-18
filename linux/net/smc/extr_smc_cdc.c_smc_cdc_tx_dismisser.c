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
struct smc_wr_tx_pend_priv {int dummy; } ;
struct smc_cdc_tx_pend {int /*<<< orphan*/ * conn; } ;

/* Variables and functions */

__attribute__((used)) static void smc_cdc_tx_dismisser(struct smc_wr_tx_pend_priv *tx_pend)
{
	struct smc_cdc_tx_pend *cdc_pend =
		(struct smc_cdc_tx_pend *)tx_pend;

	cdc_pend->conn = NULL;
}