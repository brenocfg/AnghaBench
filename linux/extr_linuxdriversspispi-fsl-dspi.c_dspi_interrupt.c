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
typedef  int u16 ;
struct spi_message {int actual_length; } ;
struct fsl_dspi {int bytes_per_word; int waitflags; TYPE_2__* pdev; int /*<<< orphan*/  waitq; int /*<<< orphan*/  len; TYPE_1__* devtype_data; int /*<<< orphan*/  regmap; struct spi_message* cur_msg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum dspi_trans_mode { ____Placeholder_dspi_trans_mode } dspi_trans_mode ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int trans_mode; } ;

/* Variables and functions */
#define  DSPI_EOQ_MODE 129 
#define  DSPI_TCFQ_MODE 128 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SPI_SR ; 
 int SPI_SR_EOQF ; 
 int SPI_SR_TCFQF ; 
 int /*<<< orphan*/  SPI_TCR ; 
 int SPI_TCR_GET_TCNT (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dspi_eoq_read (struct fsl_dspi*) ; 
 int /*<<< orphan*/  dspi_eoq_write (struct fsl_dspi*) ; 
 int /*<<< orphan*/  dspi_tcfq_read (struct fsl_dspi*) ; 
 int /*<<< orphan*/  dspi_tcfq_write (struct fsl_dspi*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t dspi_interrupt(int irq, void *dev_id)
{
	struct fsl_dspi *dspi = (struct fsl_dspi *)dev_id;
	struct spi_message *msg = dspi->cur_msg;
	enum dspi_trans_mode trans_mode;
	u32 spi_sr, spi_tcr;
	u16 spi_tcnt;

	regmap_read(dspi->regmap, SPI_SR, &spi_sr);
	regmap_write(dspi->regmap, SPI_SR, spi_sr);


	if (spi_sr & (SPI_SR_EOQF | SPI_SR_TCFQF)) {
		/* Get transfer counter (in number of SPI transfers). It was
		 * reset to 0 when transfer(s) were started.
		 */
		regmap_read(dspi->regmap, SPI_TCR, &spi_tcr);
		spi_tcnt = SPI_TCR_GET_TCNT(spi_tcr);
		/* Update total number of bytes that were transferred */
		msg->actual_length += spi_tcnt * dspi->bytes_per_word;

		trans_mode = dspi->devtype_data->trans_mode;
		switch (trans_mode) {
		case DSPI_EOQ_MODE:
			dspi_eoq_read(dspi);
			break;
		case DSPI_TCFQ_MODE:
			dspi_tcfq_read(dspi);
			break;
		default:
			dev_err(&dspi->pdev->dev, "unsupported trans_mode %u\n",
				trans_mode);
				return IRQ_HANDLED;
		}

		if (!dspi->len) {
			dspi->waitflags = 1;
			wake_up_interruptible(&dspi->waitq);
		} else {
			switch (trans_mode) {
			case DSPI_EOQ_MODE:
				dspi_eoq_write(dspi);
				break;
			case DSPI_TCFQ_MODE:
				dspi_tcfq_write(dspi);
				break;
			default:
				dev_err(&dspi->pdev->dev,
					"unsupported trans_mode %u\n",
					trans_mode);
			}
		}
	}

	return IRQ_HANDLED;
}