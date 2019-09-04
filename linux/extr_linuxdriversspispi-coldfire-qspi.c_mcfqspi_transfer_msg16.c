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
typedef  unsigned int u16 ;
struct mcfqspi {int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
 scalar_t__ MCFQSPI_QAR_CMDBUF ; 
 scalar_t__ MCFQSPI_QAR_RXBUF ; 
 scalar_t__ MCFQSPI_QAR_TXBUF ; 
 int /*<<< orphan*/  MCFQSPI_QCR_BITSE ; 
 int /*<<< orphan*/  MCFQSPI_QDLYR_SPE ; 
 int /*<<< orphan*/  mcfqspi_qdlyr_spe (struct mcfqspi*) ; 
 void* mcfqspi_rd_qdr (struct mcfqspi*) ; 
 int /*<<< orphan*/  mcfqspi_wr_qar (struct mcfqspi*,scalar_t__) ; 
 int /*<<< orphan*/  mcfqspi_wr_qdlyr (struct mcfqspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcfqspi_wr_qdr (struct mcfqspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcfqspi_wr_qwr (struct mcfqspi*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mcfqspi_transfer_msg16(struct mcfqspi *mcfqspi, unsigned count,
				   const u16 *txbuf, u16 *rxbuf)
{
	unsigned i, n, offset = 0;

	n = min(count, 16u);

	mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_CMDBUF);
	for (i = 0; i < n; ++i)
		mcfqspi_wr_qdr(mcfqspi, MCFQSPI_QCR_BITSE);

	mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_TXBUF);
	if (txbuf)
		for (i = 0; i < n; ++i)
			mcfqspi_wr_qdr(mcfqspi, *txbuf++);
	else
		for (i = 0; i < count; ++i)
			mcfqspi_wr_qdr(mcfqspi, 0);

	count -= n;
	if (count) {
		u16 qwr = 0xf08;
		mcfqspi_wr_qwr(mcfqspi, 0x700);
		mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);

		do {
			wait_event(mcfqspi->waitq, !mcfqspi_qdlyr_spe(mcfqspi));
			mcfqspi_wr_qwr(mcfqspi, qwr);
			mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);
			if (rxbuf) {
				mcfqspi_wr_qar(mcfqspi,
					       MCFQSPI_QAR_RXBUF + offset);
				for (i = 0; i < 8; ++i)
					*rxbuf++ = mcfqspi_rd_qdr(mcfqspi);
			}
			n = min(count, 8u);
			if (txbuf) {
				mcfqspi_wr_qar(mcfqspi,
					       MCFQSPI_QAR_TXBUF + offset);
				for (i = 0; i < n; ++i)
					mcfqspi_wr_qdr(mcfqspi, *txbuf++);
			}
			qwr = (offset ? 0x808 : 0x000) + ((n - 1) << 8);
			offset ^= 8;
			count -= n;
		} while (count);
		wait_event(mcfqspi->waitq, !mcfqspi_qdlyr_spe(mcfqspi));
		mcfqspi_wr_qwr(mcfqspi, qwr);
		mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);
		if (rxbuf) {
			mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_RXBUF + offset);
			for (i = 0; i < 8; ++i)
				*rxbuf++ = mcfqspi_rd_qdr(mcfqspi);
			offset ^= 8;
		}
	} else {
		mcfqspi_wr_qwr(mcfqspi, (n - 1) << 8);
		mcfqspi_wr_qdlyr(mcfqspi, MCFQSPI_QDLYR_SPE);
	}
	wait_event(mcfqspi->waitq, !mcfqspi_qdlyr_spe(mcfqspi));
	if (rxbuf) {
		mcfqspi_wr_qar(mcfqspi, MCFQSPI_QAR_RXBUF + offset);
		for (i = 0; i < n; ++i)
			*rxbuf++ = mcfqspi_rd_qdr(mcfqspi);
	}
}