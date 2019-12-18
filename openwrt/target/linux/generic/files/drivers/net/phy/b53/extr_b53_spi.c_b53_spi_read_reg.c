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
 int B53_SPI_CMD_NORMAL ; 
 int B53_SPI_CMD_READ ; 
 int spi_write_then_read (struct spi_device*,int*,int,int*,unsigned int) ; 

__attribute__((used)) static inline int b53_spi_read_reg(struct spi_device *spi, u8 reg, u8 *val,
				     unsigned len)
{
	u8 txbuf[2];

	txbuf[0] = B53_SPI_CMD_NORMAL | B53_SPI_CMD_READ;
	txbuf[1] = reg;

	return spi_write_then_read(spi, txbuf, 2, val, len);
}