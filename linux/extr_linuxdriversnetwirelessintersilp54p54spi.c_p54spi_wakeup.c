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
struct p54s_priv {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SPI_ADRS_ARM_INTERRUPTS ; 
 int /*<<< orphan*/  SPI_ADRS_HOST_INTERRUPTS ; 
 int /*<<< orphan*/  SPI_HOST_INT_READY ; 
 int /*<<< orphan*/  SPI_TARGET_INT_WAKEUP ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p54spi_int_ack (struct p54s_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54spi_wait_bit (struct p54s_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54spi_write32 (struct p54s_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p54spi_wakeup(struct p54s_priv *priv)
{
	/* wake the chip */
	p54spi_write32(priv, SPI_ADRS_ARM_INTERRUPTS,
		       cpu_to_le32(SPI_TARGET_INT_WAKEUP));

	/* And wait for the READY interrupt */
	if (!p54spi_wait_bit(priv, SPI_ADRS_HOST_INTERRUPTS,
			     SPI_HOST_INT_READY)) {
		dev_err(&priv->spi->dev, "INT_READY timeout\n");
		return -EBUSY;
	}

	p54spi_int_ack(priv, SPI_HOST_INT_READY);
	return 0;
}