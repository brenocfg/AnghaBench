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
struct lbs_private {int /*<<< orphan*/  fw_ready; struct if_sdio_card* card; } ;
struct if_sdio_card {int /*<<< orphan*/  pwron_waitq; TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int if_sdio_power_on (struct if_sdio_card*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int if_sdio_power_restore(struct lbs_private *priv)
{
	struct if_sdio_card *card = priv->card;
	int r;

	/* Make sure the card will not be powered off by runtime PM */
	pm_runtime_get_sync(&card->func->dev);

	r = if_sdio_power_on(card);
	if (r)
		return r;

	wait_event(card->pwron_waitq, priv->fw_ready);
	return 0;
}