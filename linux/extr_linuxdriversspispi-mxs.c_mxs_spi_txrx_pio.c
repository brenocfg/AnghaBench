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
struct mxs_ssp {scalar_t__ devid; scalar_t__ base; } ;
struct mxs_spi {struct mxs_ssp ssp; } ;

/* Variables and functions */
 unsigned char BM_SSP_CTRL0_DATA_XFER ; 
 unsigned char BM_SSP_CTRL0_IGNORE_CRC ; 
 unsigned char BM_SSP_CTRL0_READ ; 
 unsigned char BM_SSP_CTRL0_RUN ; 
 unsigned char BM_SSP_CTRL0_XFER_COUNT ; 
 unsigned char BM_SSP_STATUS_FIFO_EMPTY ; 
 int ETIMEDOUT ; 
 scalar_t__ HW_SSP_CTRL0 ; 
 scalar_t__ HW_SSP_DATA (struct mxs_ssp*) ; 
 scalar_t__ HW_SSP_STATUS (struct mxs_ssp*) ; 
 scalar_t__ HW_SSP_XFER_SIZE ; 
 scalar_t__ IMX23_SSP ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 unsigned int TXRX_DEASSERT_CS ; 
 unsigned int TXRX_WRITE ; 
 scalar_t__ mxs_ssp_wait (struct mxs_spi*,scalar_t__,unsigned char,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned char,scalar_t__) ; 

__attribute__((used)) static int mxs_spi_txrx_pio(struct mxs_spi *spi,
			    unsigned char *buf, int len,
			    unsigned int flags)
{
	struct mxs_ssp *ssp = &spi->ssp;

	writel(BM_SSP_CTRL0_IGNORE_CRC,
	       ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_CLR);

	while (len--) {
		if (len == 0 && (flags & TXRX_DEASSERT_CS))
			writel(BM_SSP_CTRL0_IGNORE_CRC,
			       ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);

		if (ssp->devid == IMX23_SSP) {
			writel(BM_SSP_CTRL0_XFER_COUNT,
				ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_CLR);
			writel(1,
				ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);
		} else {
			writel(1, ssp->base + HW_SSP_XFER_SIZE);
		}

		if (flags & TXRX_WRITE)
			writel(BM_SSP_CTRL0_READ,
				ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_CLR);
		else
			writel(BM_SSP_CTRL0_READ,
				ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);

		writel(BM_SSP_CTRL0_RUN,
				ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);

		if (mxs_ssp_wait(spi, HW_SSP_CTRL0, BM_SSP_CTRL0_RUN, 1))
			return -ETIMEDOUT;

		if (flags & TXRX_WRITE)
			writel(*buf, ssp->base + HW_SSP_DATA(ssp));

		writel(BM_SSP_CTRL0_DATA_XFER,
			     ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);

		if (!(flags & TXRX_WRITE)) {
			if (mxs_ssp_wait(spi, HW_SSP_STATUS(ssp),
						BM_SSP_STATUS_FIFO_EMPTY, 0))
				return -ETIMEDOUT;

			*buf = (readl(ssp->base + HW_SSP_DATA(ssp)) & 0xff);
		}

		if (mxs_ssp_wait(spi, HW_SSP_CTRL0, BM_SSP_CTRL0_RUN, 0))
			return -ETIMEDOUT;

		buf++;
	}

	if (len <= 0)
		return 0;

	return -ETIMEDOUT;
}