#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct lantiq_ssc_spi {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; TYPE_2__* master; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* cur_msg; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  LTQ_SPI_STAT ; 
 int LTQ_SPI_STAT_AE ; 
 int LTQ_SPI_STAT_ERRORS ; 
 int LTQ_SPI_STAT_ME ; 
 int LTQ_SPI_STAT_RE ; 
 int LTQ_SPI_STAT_RUE ; 
 int LTQ_SPI_STAT_TE ; 
 int LTQ_SPI_STAT_TUE ; 
 int /*<<< orphan*/  LTQ_SPI_WHBSTATE ; 
 int /*<<< orphan*/  LTQ_SPI_WHBSTATE_CLR_ERRORS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lantiq_ssc_maskl (struct lantiq_ssc_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lantiq_ssc_readl (struct lantiq_ssc_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t lantiq_ssc_err_interrupt(int irq, void *data)
{
	struct lantiq_ssc_spi *spi = data;
	u32 stat = lantiq_ssc_readl(spi, LTQ_SPI_STAT);

	if (!(stat & LTQ_SPI_STAT_ERRORS))
		return IRQ_NONE;

	if (stat & LTQ_SPI_STAT_RUE)
		dev_err(spi->dev, "receive underflow error\n");
	if (stat & LTQ_SPI_STAT_TUE)
		dev_err(spi->dev, "transmit underflow error\n");
	if (stat & LTQ_SPI_STAT_AE)
		dev_err(spi->dev, "abort error\n");
	if (stat & LTQ_SPI_STAT_RE)
		dev_err(spi->dev, "receive overflow error\n");
	if (stat & LTQ_SPI_STAT_TE)
		dev_err(spi->dev, "transmit overflow error\n");
	if (stat & LTQ_SPI_STAT_ME)
		dev_err(spi->dev, "mode error\n");

	/* Clear error flags */
	lantiq_ssc_maskl(spi, 0, LTQ_SPI_WHBSTATE_CLR_ERRORS, LTQ_SPI_WHBSTATE);

	/* set bad status so it can be retried */
	if (spi->master->cur_msg)
		spi->master->cur_msg->status = -EIO;
	queue_work(spi->wq, &spi->work);

	return IRQ_HANDLED;
}