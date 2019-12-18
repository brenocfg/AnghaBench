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
struct smc_link {int dummy; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */

__attribute__((used)) static void smc_llc_tx_handler(struct smc_wr_tx_pend_priv *pend,
			       struct smc_link *link,
			       enum ib_wc_status wc_status)
{
	/* future work: handle wc_status error for recovery and failover */
}