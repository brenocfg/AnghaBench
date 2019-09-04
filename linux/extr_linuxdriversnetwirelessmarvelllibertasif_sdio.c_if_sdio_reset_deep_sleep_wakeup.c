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
struct lbs_private {int /*<<< orphan*/  dev; struct if_sdio_card* card; } ;
struct if_sdio_card {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIGURATION_REG ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int if_sdio_reset_deep_sleep_wakeup(struct lbs_private *priv)
{
	struct if_sdio_card *card = priv->card;
	int ret = -1;

	sdio_claim_host(card->func);

	sdio_writeb(card->func, 0, CONFIGURATION_REG, &ret);
	if (ret)
		netdev_err(priv->dev, "sdio_writeb failed!\n");

	sdio_release_host(card->func);

	return ret;

}