#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct fsl_espi {unsigned int tx_pos; int tx_done; TYPE_1__* tx_t; scalar_t__ rxskip; int /*<<< orphan*/  m_transfers; scalar_t__ swab; } ;
struct TYPE_3__ {unsigned int len; void* tx_buf; int /*<<< orphan*/  transfer_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESPI_SPITF ; 
 scalar_t__ FSL_ESPI_FIFO_SIZE ; 
 scalar_t__ SPIE_TXCNT (scalar_t__) ; 
 int /*<<< orphan*/  fsl_espi_write_reg (struct fsl_espi*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fsl_espi_write_reg16 (struct fsl_espi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_espi_write_reg8 (struct fsl_espi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* list_next_entry (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  swab16p (void const*) ; 
 scalar_t__ swahb32p (void const*) ; 
 int /*<<< orphan*/  transfer_list ; 

__attribute__((used)) static void fsl_espi_fill_tx_fifo(struct fsl_espi *espi, u32 events)
{
	u32 tx_fifo_avail;
	unsigned int tx_left;
	const void *tx_buf;

	/* if events is zero transfer has not started and tx fifo is empty */
	tx_fifo_avail = events ? SPIE_TXCNT(events) :  FSL_ESPI_FIFO_SIZE;
start:
	tx_left = espi->tx_t->len - espi->tx_pos;
	tx_buf = espi->tx_t->tx_buf;
	while (tx_fifo_avail >= min(4U, tx_left) && tx_left) {
		if (tx_left >= 4) {
			if (!tx_buf)
				fsl_espi_write_reg(espi, ESPI_SPITF, 0);
			else if (espi->swab)
				fsl_espi_write_reg(espi, ESPI_SPITF,
					swahb32p(tx_buf + espi->tx_pos));
			else
				fsl_espi_write_reg(espi, ESPI_SPITF,
					*(u32 *)(tx_buf + espi->tx_pos));
			espi->tx_pos += 4;
			tx_left -= 4;
			tx_fifo_avail -= 4;
		} else if (tx_left >= 2 && tx_buf && espi->swab) {
			fsl_espi_write_reg16(espi, ESPI_SPITF,
					swab16p(tx_buf + espi->tx_pos));
			espi->tx_pos += 2;
			tx_left -= 2;
			tx_fifo_avail -= 2;
		} else {
			if (!tx_buf)
				fsl_espi_write_reg8(espi, ESPI_SPITF, 0);
			else
				fsl_espi_write_reg8(espi, ESPI_SPITF,
					*(u8 *)(tx_buf + espi->tx_pos));
			espi->tx_pos += 1;
			tx_left -= 1;
			tx_fifo_avail -= 1;
		}
	}

	if (!tx_left) {
		/* Last transfer finished, in rxskip mode only one is needed */
		if (list_is_last(&espi->tx_t->transfer_list,
		    espi->m_transfers) || espi->rxskip) {
			espi->tx_done = true;
			return;
		}
		espi->tx_t = list_next_entry(espi->tx_t, transfer_list);
		espi->tx_pos = 0;
		/* continue with next transfer if tx fifo is not full */
		if (tx_fifo_avail)
			goto start;
	}
}