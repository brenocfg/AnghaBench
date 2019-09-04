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
struct spi_device {int /*<<< orphan*/  irq; } ;
struct lbs_private {int dummy; } ;
struct if_spi_card {TYPE_1__* pdata; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  resume_work; struct lbs_private* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* teardown ) (struct spi_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_if_spi_card (struct if_spi_card*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct if_spi_card*) ; 
 int /*<<< orphan*/  lbs_deb_spi (char*) ; 
 int /*<<< orphan*/  lbs_remove_card (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_stop_card (struct lbs_private*) ; 
 struct if_spi_card* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  stub1 (struct spi_device*) ; 

__attribute__((used)) static int libertas_spi_remove(struct spi_device *spi)
{
	struct if_spi_card *card = spi_get_drvdata(spi);
	struct lbs_private *priv = card->priv;

	lbs_deb_spi("libertas_spi_remove\n");

	cancel_work_sync(&card->resume_work);

	lbs_stop_card(priv);
	lbs_remove_card(priv); /* will call free_netdev */

	free_irq(spi->irq, card);
	destroy_workqueue(card->workqueue);
	if (card->pdata->teardown)
		card->pdata->teardown(spi);
	free_if_spi_card(card);

	return 0;
}