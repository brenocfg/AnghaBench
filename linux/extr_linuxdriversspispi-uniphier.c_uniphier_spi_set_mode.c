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
typedef  int u32 ;
struct uniphier_spi_priv {scalar_t__ base; } ;
struct spi_device {int mode; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 int SPI_LSB_FIRST ; 
#define  SPI_MODE_0 131 
#define  SPI_MODE_1 130 
#define  SPI_MODE_2 129 
#define  SPI_MODE_3 128 
 scalar_t__ SSI_CKS ; 
 int SSI_CKS_CKDLY ; 
 int SSI_CKS_CKINIT ; 
 int SSI_CKS_CKPHS ; 
 scalar_t__ SSI_FPS ; 
 int SSI_FPS_FSPOL ; 
 int SSI_FPS_FSTRT ; 
 scalar_t__ SSI_RXWDS ; 
 scalar_t__ SSI_TXWDS ; 
 int /*<<< orphan*/  SSI_TXWDS_TDTF_MASK ; 
 struct uniphier_spi_priv* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_spi_set_mode(struct spi_device *spi)
{
	struct uniphier_spi_priv *priv = spi_master_get_devdata(spi->master);
	u32 val1, val2;

	/*
	 * clock setting
	 * CKPHS    capture timing. 0:rising edge, 1:falling edge
	 * CKINIT   clock initial level. 0:low, 1:high
	 * CKDLY    clock delay. 0:no delay, 1:delay depending on FSTRT
	 *          (FSTRT=0: 1 clock, FSTRT=1: 0.5 clock)
	 *
	 * frame setting
	 * FSPOL    frame signal porarity. 0: low, 1: high
	 * FSTRT    start frame timing
	 *          0: rising edge of clock, 1: falling edge of clock
	 */
	switch (spi->mode & (SPI_CPOL | SPI_CPHA)) {
	case SPI_MODE_0:
		/* CKPHS=1, CKINIT=0, CKDLY=1, FSTRT=0 */
		val1 = SSI_CKS_CKPHS | SSI_CKS_CKDLY;
		val2 = 0;
		break;
	case SPI_MODE_1:
		/* CKPHS=0, CKINIT=0, CKDLY=0, FSTRT=1 */
		val1 = 0;
		val2 = SSI_FPS_FSTRT;
		break;
	case SPI_MODE_2:
		/* CKPHS=0, CKINIT=1, CKDLY=1, FSTRT=1 */
		val1 = SSI_CKS_CKINIT | SSI_CKS_CKDLY;
		val2 = SSI_FPS_FSTRT;
		break;
	case SPI_MODE_3:
		/* CKPHS=1, CKINIT=1, CKDLY=0, FSTRT=0 */
		val1 = SSI_CKS_CKPHS | SSI_CKS_CKINIT;
		val2 = 0;
		break;
	}

	if (!(spi->mode & SPI_CS_HIGH))
		val2 |= SSI_FPS_FSPOL;

	writel(val1, priv->base + SSI_CKS);
	writel(val2, priv->base + SSI_FPS);

	val1 = 0;
	if (spi->mode & SPI_LSB_FIRST)
		val1 |= FIELD_PREP(SSI_TXWDS_TDTF_MASK, 1);
	writel(val1, priv->base + SSI_TXWDS);
	writel(val1, priv->base + SSI_RXWDS);
}