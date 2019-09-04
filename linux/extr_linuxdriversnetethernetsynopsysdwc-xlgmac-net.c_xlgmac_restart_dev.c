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
struct xlgmac_pdata {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlgmac_free_rx_data (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_free_tx_data (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_start (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_stop (struct xlgmac_pdata*) ; 

__attribute__((used)) static void xlgmac_restart_dev(struct xlgmac_pdata *pdata)
{
	/* If not running, "restart" will happen on open */
	if (!netif_running(pdata->netdev))
		return;

	xlgmac_stop(pdata);

	xlgmac_free_tx_data(pdata);
	xlgmac_free_rx_data(pdata);

	xlgmac_start(pdata);
}