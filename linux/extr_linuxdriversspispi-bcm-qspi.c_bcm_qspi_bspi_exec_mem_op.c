#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int nbytes; } ;
struct TYPE_5__ {scalar_t__ nbytes; int val; } ;
struct spi_mem_op {TYPE_3__ data; TYPE_1__ addr; } ;
struct spi_device {int /*<<< orphan*/  chip_select; int /*<<< orphan*/  master; } ;
struct bcm_qspi_soc_intc {int /*<<< orphan*/  (* bcm_qspi_int_set ) (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* bcm_qspi_int_ack ) (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  flex_mode; } ;
struct bcm_qspi {int bspi_rf_op_len; TYPE_4__* pdev; int /*<<< orphan*/  bspi_done; struct bcm_qspi_soc_intc* soc_intc; scalar_t__ bspi_rf_op_status; struct spi_mem_op const* bspi_rf_op; scalar_t__ bspi_rf_op_idx; TYPE_2__ xfer_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSPI ; 
 scalar_t__ BSPI_ADDRLEN_4BYTES ; 
 int /*<<< orphan*/  BSPI_BSPI_FLASH_UPPER_ADDR_BYTE ; 
 int /*<<< orphan*/  BSPI_DONE ; 
 int /*<<< orphan*/  BSPI_RAF_NUM_WORDS ; 
 int /*<<< orphan*/  BSPI_RAF_START_ADDR ; 
 int /*<<< orphan*/  BSPI_RAF_WATERMARK ; 
 int BSPI_READ_LENGTH ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MSPI ; 
 int /*<<< orphan*/  MSPI_BSPI_DONE ; 
 int /*<<< orphan*/  MSPI_WRITE_LOCK ; 
 int /*<<< orphan*/  bcm_qspi_bspi_lr_start (struct bcm_qspi*) ; 
 int bcm_qspi_bspi_ver_three (struct bcm_qspi*) ; 
 int /*<<< orphan*/  bcm_qspi_chip_select (struct bcm_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_qspi_enable_bspi (struct bcm_qspi*) ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mb () ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct bcm_qspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct bcm_qspi_soc_intc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bcm_qspi_bspi_exec_mem_op(struct spi_device *spi,
				     const struct spi_mem_op *op)
{
	struct bcm_qspi *qspi = spi_master_get_devdata(spi->master);
	u32 addr = 0, len, rdlen, len_words, from = 0;
	int ret = 0;
	unsigned long timeo = msecs_to_jiffies(100);
	struct bcm_qspi_soc_intc *soc_intc = qspi->soc_intc;

	if (bcm_qspi_bspi_ver_three(qspi))
		if (op->addr.nbytes == BSPI_ADDRLEN_4BYTES)
			return -EIO;

	from = op->addr.val;
	bcm_qspi_chip_select(qspi, spi->chip_select);
	bcm_qspi_write(qspi, MSPI, MSPI_WRITE_LOCK, 0);

	/*
	 * when using flex mode we need to send
	 * the upper address byte to bspi
	 */
	if (bcm_qspi_bspi_ver_three(qspi) == false) {
		addr = from & 0xff000000;
		bcm_qspi_write(qspi, BSPI,
			       BSPI_BSPI_FLASH_UPPER_ADDR_BYTE, addr);
	}

	if (!qspi->xfer_mode.flex_mode)
		addr = from;
	else
		addr = from & 0x00ffffff;

	if (bcm_qspi_bspi_ver_three(qspi) == true)
		addr = (addr + 0xc00000) & 0xffffff;

	/*
	 * read into the entire buffer by breaking the reads
	 * into RAF buffer read lengths
	 */
	len = op->data.nbytes;
	qspi->bspi_rf_op_idx = 0;

	do {
		if (len > BSPI_READ_LENGTH)
			rdlen = BSPI_READ_LENGTH;
		else
			rdlen = len;

		reinit_completion(&qspi->bspi_done);
		bcm_qspi_enable_bspi(qspi);
		len_words = (rdlen + 3) >> 2;
		qspi->bspi_rf_op = op;
		qspi->bspi_rf_op_status = 0;
		qspi->bspi_rf_op_len = rdlen;
		dev_dbg(&qspi->pdev->dev,
			"bspi xfr addr 0x%x len 0x%x", addr, rdlen);
		bcm_qspi_write(qspi, BSPI, BSPI_RAF_START_ADDR, addr);
		bcm_qspi_write(qspi, BSPI, BSPI_RAF_NUM_WORDS, len_words);
		bcm_qspi_write(qspi, BSPI, BSPI_RAF_WATERMARK, 0);
		if (qspi->soc_intc) {
			/*
			 * clear soc MSPI and BSPI interrupts and enable
			 * BSPI interrupts.
			 */
			soc_intc->bcm_qspi_int_ack(soc_intc, MSPI_BSPI_DONE);
			soc_intc->bcm_qspi_int_set(soc_intc, BSPI_DONE, true);
		}

		/* Must flush previous writes before starting BSPI operation */
		mb();
		bcm_qspi_bspi_lr_start(qspi);
		if (!wait_for_completion_timeout(&qspi->bspi_done, timeo)) {
			dev_err(&qspi->pdev->dev, "timeout waiting for BSPI\n");
			ret = -ETIMEDOUT;
			break;
		}

		/* set msg return length */
		addr += rdlen;
		len -= rdlen;
	} while (len);

	return ret;
}