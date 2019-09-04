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
struct sdio_func {int dummy; } ;
struct rsi_hw {scalar_t__ rsi_dev; } ;
struct rsi_91x_sdiodev {int write_fail; int /*<<< orphan*/  rx_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_ZONE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rsi_91x_deinit (struct rsi_hw*) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsi_kill_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsi_mac80211_detach (struct rsi_hw*) ; 
 int /*<<< orphan*/  rsi_reset_card (struct sdio_func*) ; 
 int /*<<< orphan*/  rsi_reset_chip (struct rsi_hw*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 struct rsi_hw* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 

__attribute__((used)) static void rsi_disconnect(struct sdio_func *pfunction)
{
	struct rsi_hw *adapter = sdio_get_drvdata(pfunction);
	struct rsi_91x_sdiodev *dev;

	if (!adapter)
		return;

	dev = (struct rsi_91x_sdiodev *)adapter->rsi_dev;

	rsi_kill_thread(&dev->rx_thread);
	sdio_claim_host(pfunction);
	sdio_release_irq(pfunction);
	sdio_release_host(pfunction);
	mdelay(10);

	rsi_mac80211_detach(adapter);
	mdelay(10);

	/* Reset Chip */
	rsi_reset_chip(adapter);

	/* Resetting to take care of the case, where-in driver is re-loaded */
	sdio_claim_host(pfunction);
	rsi_reset_card(pfunction);
	sdio_disable_func(pfunction);
	sdio_release_host(pfunction);
	dev->write_fail = 2;
	rsi_91x_deinit(adapter);
	rsi_dbg(ERR_ZONE, "##### RSI SDIO device disconnected #####\n");

}