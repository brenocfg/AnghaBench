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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCF2123_WRITE ; 
 int /*<<< orphan*/  pcf2123_delay_trec () ; 
 int spi_write (struct spi_device*,int /*<<< orphan*/ *,size_t) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int pcf2123_write(struct device *dev, u8 *txbuf, size_t size)
{
	struct spi_device *spi = to_spi_device(dev);
	int ret;

	txbuf[0] |= PCF2123_WRITE;
	ret = spi_write(spi, txbuf, size);
	pcf2123_delay_trec();

	return ret;
}