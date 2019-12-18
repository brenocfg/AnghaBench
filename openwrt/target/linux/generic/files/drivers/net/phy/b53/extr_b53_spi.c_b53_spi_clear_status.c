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
typedef  int u8 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int B53_SPI_CMD_SPIF ; 
 int /*<<< orphan*/  B53_SPI_STATUS ; 
 int EIO ; 
 int b53_spi_read_reg (struct spi_device*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static inline int b53_spi_clear_status(struct spi_device *spi)
{
	unsigned int i;
	u8 rxbuf;
	int ret;

	for (i = 0; i < 10; i++) {
		ret = b53_spi_read_reg(spi, B53_SPI_STATUS, &rxbuf, 1);
		if (ret)
			return ret;

		if (!(rxbuf & B53_SPI_CMD_SPIF))
			break;

		mdelay(1);
	}

	if (i == 10)
		return -EIO;

	return 0;
}